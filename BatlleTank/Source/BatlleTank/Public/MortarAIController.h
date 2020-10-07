// Copyright N01 Ltda.

#pragma once
#include "AIController.h"
#include "MortarAIController.generated.h"

/**
 *  Here is set how the mortar AI will behave
 */
UCLASS(hidecategories = ("Cooking", "LOD", "Input", "Replication", "Actor"))
class BATLLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void Tick(float DeltaTime) override;

};
