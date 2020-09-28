// Copyright N01 Ltda.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Useful class created in order to add a fly-by-wire layer to make AI and Player controls fair.
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATLLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "Movement")
		void Initialise(UTankTrack* SetRightTrack, UTankTrack* SetLeftTrack);

		UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveForwardIntention(float Force);

		UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveRightIntention(float Force);

	private:
		// called from the pathfinding logic by the AI controllers (MoveToActor() method).
		virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

		UTankTrack* RightTrack = nullptr;
		UTankTrack* LeftTrack = nullptr;
};
