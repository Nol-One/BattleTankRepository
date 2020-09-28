// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


AProjectile::AProjectile()
{
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));

    ProjectileMovement->bAutoActivate = false; // means that no launching occurs when the component is created.
}

void AProjectile::LaunchProjectile(float Speed)
{
    // no need to protect pointers because the component is being created at the constructor.
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate();
}