// Copyright N01 Ltda.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

// forward declarations
class ATank; 

UCLASS()
class BATLLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditDefaultsOnly)
		float StopDistance = 3000.0; // sensible default distance which AI can get to the player

	private:
		virtual void Tick(float DeltaTime) override;
};
