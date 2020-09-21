// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// forward declarations
class ATank; 

UCLASS()
class BATLLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	private:
		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

		ATank* GetControlledTank() const;

		UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;

		UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.33333f;

		UPROPERTY(EditAnywhere)
		float Reach = 100000.0f;

		void AimTowardsCrosshair();

		bool CrosshairRaycast(FHitResult& Hit); // Make the tank shoots through where the crosshair is

		bool GetCrosshairVector(FVector& AimDirection) const;
};
