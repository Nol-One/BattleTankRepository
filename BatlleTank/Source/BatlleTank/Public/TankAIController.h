// Copyright N01 Ltda.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATLLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	protected:
		UPROPERTY(EditDefaultsOnly)
		float StopDistance = 8000.0; // sensible default distance which AI can get to the player

	private:
		virtual void Tick(float DeltaTime) override;
};
