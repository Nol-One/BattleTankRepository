// Copyright N01 Ltda.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// forward declarations
class ATank; 

UCLASS()
class BATLLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	protected:
		UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

		UFUNCTION(BlueprintImplementableEvent, Category = "Aiming")
		void FoundAimingComponent(UTankAimingComponent* TankAimingComponent);

	private:
		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

		UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;

		UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333f;

		UPROPERTY(EditDefaultsOnly)
		float Reach = 100000.0f;

		void AimTowardsCrosshair();

		bool CrosshairRaycast(FHitResult& Hit); // Make the tank shoots through where the crosshair is

		bool GetCrosshairVector(FVector& AimDirection) const;
};
