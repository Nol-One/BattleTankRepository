// Copyright N01 Ltda.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision", "Cooking", "Mobile"))
class BATLLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

	public:
	void RotateTurret(float RelativeSpeed);

	private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 50.0f; // sensible default value
};
