// Copyright N01 Ltda.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward declarations
class UTankBarrel; 
class AProjectile;

UCLASS()
class BATLLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable)
		void Fire();

	private:	
		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.0f; // sensible default value

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> Projectile_BP;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeSeconds = 3.0f;

		// local reference to be used in the firing method 
		UTankBarrel* Barrel = nullptr;

		float LastFireTime = 0.0f;
};
