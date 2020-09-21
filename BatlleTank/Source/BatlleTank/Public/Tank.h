// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward declarations
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATLLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	protected:
		UTankAimingComponent* TankAimingComponent = nullptr;

	public:
		ATank(); //Constructor

		UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

		UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* Turret);

		void AimAt(FVector HitLocation);

	private:	
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000.0f;
};
