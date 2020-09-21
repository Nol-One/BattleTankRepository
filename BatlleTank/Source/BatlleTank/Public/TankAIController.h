// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

// forward declarations
class ATank; 

UCLASS()
class BATLLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	private:
		virtual void Tick(float DeltaTime) override;

		ATank* GetControlledTank() const;

		ATank* GetPlayerTank() const;
};
