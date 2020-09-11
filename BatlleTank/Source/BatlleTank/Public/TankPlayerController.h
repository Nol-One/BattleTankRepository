// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATLLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		void BeginPlay() override;

		void Tick(float DeltaTime) override;

		ATank* GetControlledTank() const;

	private:
		void AimTowardsCrosshair(); // Make the tank shoots through where the crosshair is
};
