// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATLLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

	public:
		void LaunchProjectile(float Speed);

	private:
		AProjectile(); // constructor

		UProjectileMovementComponent* ProjectileMovement;
};
