// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

UCLASS()
class BATLLETANK_API ATankAIController : public AAIController
{
	public:
		GENERATED_BODY()
		
		void BeginPlay() override;

	private:
		ATank* GetControlledTank() const;

		ATank* GetPlayerTank() const;
};
