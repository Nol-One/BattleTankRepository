// Copyright N01 Ltda.

#include "Tank.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"

ATank::ATank()
{
    Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
    Body->SetNotifyRigidBodyCollision(true);  // to simulate generate hit events by default
    SetRootComponent(Body);
                                // VFX STUFF
    DeathVFX = CreateDefaultSubobject<UParticleSystemComponent>(FName ("DeathVFX"));
    DeathVFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    DeathVFX->bAutoActivate = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
    FMath::RoundToInt(DamageAmount);
    auto DamageToApply = FMath::Clamp<int>(DamageAmount, 0, EnergyPoints);

    // reduce energy
    EnergyPoints -= DamageToApply;
    
    if (EnergyPoints == 0)
    {
        DeathVFX->Activate();
        // broadcasting to the facking unreals magic, see ya on the other side
        ImDead.Broadcast();
    }

    return FMath::RoundToFloat(DamageToApply);
}

float ATank::GetEnergyPercent() const
{
    return (float)EnergyPoints/100; // casts to a float and returns a decimal
}