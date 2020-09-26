// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision", "Cooking", "Mobile"))
class BATLLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
	void ElevateBarrel(float RelativeSpeed);

	private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegree = 0; // sensible default value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegree = 40; // sensible default value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10; // sensible default value
};
