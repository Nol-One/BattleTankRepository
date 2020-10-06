// Copyright N01 Ltda.

#pragma once

#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATLLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
	private:
		ASprungWheel();

		virtual void BeginPlay() override;

		void SetupConstraint();

							// COMPONENTS
		// the joint (spring/constraint) that hold mass and axle together
		UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* MassAxleConstraint = nullptr;
		// axle that is going to move the wheels
		UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Axle = nullptr;
		UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Wheel = nullptr;
		// constraint to move the wheel
		UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
};
