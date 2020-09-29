// Copyright N01 Ltda.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Used to control how the tracks work and drive the tank around.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATLLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "Input")
		void SetTrackForce(float Force);

		// max force per track, in newtons
		UPROPERTY(EditDefaultsOnly)
		float MaxDrivingForce = 40000000.0f; // sensible default value, considering 40000kg of tank mass and 10m/s (mass * acceleration)

	private:
		virtual void BeginPlay() override;

		UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

		void DriveTrack();

		void ApplyCounterSlipForce();

		float ClampedForce = 0.0f;
};
