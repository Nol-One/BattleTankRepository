// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"

AProjectile::AProjectile()
{
    // creates and defines the root component
    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);
    // setup a macro that detects hit events for the mesh from code
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
    
    // creates a particle component attached to the root component
    LaunchVFX = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch VFX"));
    LaunchVFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    // creates a particle component supposed to be activated when hits is detected
    HitVFX = CreateDefaultSubobject<UParticleSystemComponent>(FName("Hit VFX"));
    HitVFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    HitVFX->bAutoActivate = false;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate = false; // means that no launching occurs when the component is created.

	KnockbackForce = CreateDefaultSubobject<URadialForceComponent>(FName("Knockback Force"));
    KnockbackForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // deactivate the vfx from lanch from continue spawning and set the hit vfx
    LaunchVFX->Deactivate();
    HitVFX->Activate();

    // activate and apply knockback
    KnockbackForce->FireImpulse();
    
    /* Replace root component to the explosion effect, 
      and delete the physical mesh that was the previous root.*/
    SetRootComponent(KnockbackForce);
    CollisionMesh->DestroyComponent();

    FTimerHandle Timer; // discarded, used as obligatory out parameter.
    FTimerDelegate Delegate; // generic delegate
    
    // lambda taking the Destroy method from AActor (parent-class of the Projectile)
    Delegate.BindLambda( [this] { Destroy(); } );
    
    GetWorld()->GetTimerManager().SetTimer(Timer, Delegate, DestroyDelay, false);
}

void AProjectile::LaunchProjectile(float Speed)
{
    // we only activate the movement when given the speed and spawn.
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate();
}

