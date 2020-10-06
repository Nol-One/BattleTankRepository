// Copyright N01 Ltda.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/AudioComponent.h"

AProjectile::AProjectile()
{
    // creates and defines the root component
    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);
    // setup a macro that detects delegated hit events for the mesh from code.
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
    
    //component that applies a radial force when requested.
	KnockbackForce = CreateDefaultSubobject<URadialForceComponent>(FName("KnockbackForce"));
    KnockbackForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    // define the concept of launching a projectile into the world using this useful component
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
    ProjectileMovement->bAutoActivate = false; // means that no launching occurs when the component is created, only when requested.

                            /// LAUNCH VFX / SFX
    LaunchVFX = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchVFX"));
    LaunchVFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    LaunchSFX = CreateDefaultSubobject<UAudioComponent>(FName("LaunchSFX"));
    LaunchSFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

                            /// HIT VFX / SFX
    // particle/audio components to be activated when collision is detected.
    HitVFX = CreateDefaultSubobject<UParticleSystemComponent>(FName("HitVFX"));
    HitVFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    HitVFX->bAutoActivate = false;
    HitSFX = CreateDefaultSubobject<UAudioComponent>(FName("HitSFX"));
    HitSFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    HitSFX->bAutoActivate = false;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // deactivate the vfx from lanch from continue spawning and set the hit vfx
    LaunchVFX->Deactivate();
    HitVFX->Activate(); 
    HitSFX->Activate();

    // activate and apply knockback
    KnockbackForce->FireImpulse();
    
    /* Replace root component to the explosion effect, 
      and delete the physical mesh that was the previous root.*/
    SetRootComponent(KnockbackForce);
    CollisionMesh->DestroyComponent();

    UGameplayStatics::ApplyRadialDamage
    (
        this,
        BaseProjectileDamage,
        GetActorLocation(),
        KnockbackForce->Radius, // for consistency
        UDamageType::StaticClass(),
        TArray<AActor*>() // meaning damage all actors in range
    );

    /// Timer to delete the spawned object
    FTimerHandle Timer; // discarded, used as obligatory out parameter.
    FTimerDelegate Delegate; // generic delegate

    // lambda taking the Destroy method from AActor (parent-class of the AProjectile)
    Delegate.BindLambda( [this] { Destroy(); } );
    GetWorld()->GetTimerManager().SetTimer(Timer, Delegate, DestroyDelay, false);
}

void AProjectile::LaunchProjectile(float Speed)
{
    // we only activate the launch when given the speed and spawn of the mesh (projectile).
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate();
}

