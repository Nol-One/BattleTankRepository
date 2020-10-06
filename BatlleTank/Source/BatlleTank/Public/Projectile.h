// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;
class UAudioComponent;

UCLASS()
class BATLLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

	public:
		void LaunchProjectile(float Speed);

	private:
		AProjectile(); // constructor

		UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

						// ROOT COMPONENT
		UPROPERTY(VisibleAnywhere, Category = "Root")
		UStaticMeshComponent* CollisionMesh = nullptr;

						// VFX COMPONENTS
		UPROPERTY(VisibleAnywhere, Category = "VFX")
		UParticleSystemComponent* LaunchVFX = nullptr;
		UPROPERTY(VisibleAnywhere, Category = "VFX")
		UParticleSystemComponent* HitVFX = nullptr;

						// SFX COMPONENTS
		UPROPERTY(VisibleAnywhere, Category = "SFX")
		UAudioComponent* LaunchSFX = nullptr;
		UPROPERTY(VisibleAnywhere, Category = "SFX")
		UAudioComponent* HitSFX = nullptr;

						// BALLISTICS COMPONENTS
		UPROPERTY(VisibleAnywhere, Category = "Settings")
		URadialForceComponent* KnockbackForce = nullptr;
		UPROPERTY(EditDefaultsOnly, Category = "Settings")
		float DestroyDelay = 5.0f; // sensible default value
		UPROPERTY(EditDefaultsOnly, Category = "Settings")
		float BaseProjectileDamage = 10.0f; // sensible default value

		UProjectileMovementComponent* ProjectileMovement = nullptr;	
};
