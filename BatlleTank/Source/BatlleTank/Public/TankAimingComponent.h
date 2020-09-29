// Copyright N01 Ltda.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// forward declarations
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	NoTarget,
	Reloading,
	Aiming,
	Ready
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
		EFiringStatus FiringStatus = EFiringStatus::NoTarget;

	private:	
		UTankAimingComponent(); // constructor

		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

		void MoveTurretBarrelTo(FVector AimDirection);

		void IsBarrelMoving(FVector AimDirection);

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.0f; // sensible default value

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> Projectile_BP;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeSeconds = 2.5f;

		float LastFireTime = 0.0f;

		bool bTargetFound = false;
		bool bIsBarrelReady = false;

		UTankBarrel* Barrel = nullptr;
		UTankTurret* Turret = nullptr;	
};
