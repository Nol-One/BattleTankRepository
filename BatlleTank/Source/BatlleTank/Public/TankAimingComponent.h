// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declarations
class UTankBarrel; 
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATLLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	public:	
		void AimAt(FVector HitLocation, float LaunchSpeed);

		void SetBarrelReference(UTankBarrel* BarrelToSet);

		void SetTurretReference(UTankTurret* TurretToSet);

	private:	
		void MoveBarrel(FVector AimDirection);

		void MoveTurret(FVector AimDirection);
		
		UTankBarrel* Barrel = nullptr;

		UTankTurret* Turret = nullptr;
};
