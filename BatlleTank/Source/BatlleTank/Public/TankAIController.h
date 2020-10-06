// Copyright N01 Ltda.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS(hidecategories = ("LOD", "Cooking", "Input", "Actor", "Events"))
class BATLLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	protected:
		UPROPERTY(EditDefaultsOnly, Category = "AI")
		float StopDistance = 8000.0; // sensible default distance which AI can get to the player

	private:
		virtual void Tick(float DeltaTime) override;

		virtual void SetPawn(APawn* InPawn) override;

		// this method is used for the tank delegating death to call AKA "the other side"
		UFUNCTION()
		void OnDeath();
};
