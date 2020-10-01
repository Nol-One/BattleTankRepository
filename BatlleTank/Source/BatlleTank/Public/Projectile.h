// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

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

		UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent* CollisionMesh = nullptr;

		UPROPERTY(VisibleAnywhere, Category = "Component")
		UParticleSystemComponent* LaunchVFX = nullptr;

		UPROPERTY(VisibleAnywhere, Category = "Component")
		UParticleSystemComponent* HitVFX = nullptr;

		UPROPERTY(VisibleAnywhere, Category = "Component")
		URadialForceComponent* KnockbackForce = nullptr;

		UProjectileMovementComponent* ProjectileMovement = nullptr;	

		UPROPERTY(EditDefaultsOnly, Category = Firing)
		float DestroyDelay = 5; // sensible default value
};
