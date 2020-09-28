// Copyright N01 Ltda.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declarations
class UTankBarrel; 
class UTankTurret;
class AProjectile;

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
		void AimAt(FVector HitLocation);

		UFUNCTION(BlueprintCallable)
		void Fire();

	protected:
		UFUNCTION(BlueprintCallable, Category = "Aiming")
		void Initialise (UTankTurret* SetTurret, UTankBarrel* SetBarrel);

		UPROPERTY(BlueprintReadOnly, Category = "Crosshair")
		EFiringState CurrentState = EFiringState::Aiming;

	private:	
		void MoveTurretBarrelTo(FVector AimDirection);

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000.0f; // sensible default value

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> Projectile_BP;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeSeconds = 2.5f;

		float LastFireTime = 0.0f;

		UTankBarrel* Barrel = nullptr;
		UTankTurret* Turret = nullptr;	
};
