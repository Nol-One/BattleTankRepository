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
	OutOfAmmo,
	NoTarget,
	Reloading,
	Aiming,
	Ready
};

UCLASS( meta=(BlueprintSpawnableComponent), hidecategories = ("Variable", "Tags", "ComponentReplication", "Cooking", "Events", "AssetUserData", "Collision") )
class BATLLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	public:	
		EFiringStatus GetFiringStatus() const;

		UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetAmmoCount() const;

		void AimAt(FVector HitLocation);

		UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	protected:
		UFUNCTION(BlueprintCallable, Category = "Aiming")
		void Initialize (UTankTurret* SetTurret, UTankBarrel* SetBarrel);

		UPROPERTY(BlueprintReadOnly, Category = "Crosshair")
		EFiringStatus FiringStatus = EFiringStatus::NoTarget;

	private:	
		UTankAimingComponent(); // constructor

		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

		void MoveTurretBarrelTo(FVector AimDirection);

		void IsBarrelMoving(FVector AimDirection);

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 6000.0f; // sensible default value

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> Projectile_BP;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadSeconds = 2.0f;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 StartAmmo = 20; // sensible default

		float LastFireTime = 0.0f;

		bool bTargetFound = false;
		bool bIsBarrelReady = false;

		UTankBarrel* Barrel = nullptr;
		UTankTurret* Turret = nullptr;	
};
