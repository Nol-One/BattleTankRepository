// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declarations
class UTankBarrel; 
class UTankTurret;

UENUM()
enum class EFiringState : uint8
{
	NoTarget,
	Ready,
	Aiming,
	Reloading
};

UCLASS( meta=(BlueprintSpawnableComponent) )
class BATLLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	public:	
		void AimAt(FVector HitLocation, float LaunchSpeed);

	protected:
		UFUNCTION(BlueprintCallable, Category = "Aiming")
		void Initialise (UTankTurret* SetTurret, UTankBarrel* SetBarrel);

		UPROPERTY(BlueprintReadOnly, Category = "Crosshair")
		EFiringState CurrentState = EFiringState::Aiming;

	private:	
		void MoveTurretBarrelTo(FVector AimDirection);

		UTankBarrel* Barrel = nullptr;
		UTankTurret* Turret = nullptr;
};
