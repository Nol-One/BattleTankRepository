// Copyright N01 Ltda.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision", "Cooking", "Mobile", "Variable", "Navigation", "VirtualTexture", "Tags", "ComponentReplication", "Events", "MaterialParameters", "HLOD", "AssetUserData"))
class BATLLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
		void ElevateBarrel(float RelativeSpeed);

	private:
		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinElevationDegree = -5.0f; // sensible default value

		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxElevationDegree = 35.0f; // sensible default value

		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 20.0f; // sensible default value
};
