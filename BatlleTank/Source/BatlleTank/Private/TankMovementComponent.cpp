// Copyright N01 Ltda.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* SetRightTrack, UTankTrack* SetLeftTrack)
{
    RightTrack = SetRightTrack;
    LeftTrack = SetLeftTrack;
}

void UTankMovementComponent::MoveForwardIntention(float Force)
{
     if(!ensure(RightTrack && LeftTrack)) { return; } // pointers protection avoiding crashes

    RightTrack->SetTrackForce(Force);
    LeftTrack->SetTrackForce(Force);
}

void UTankMovementComponent::MoveRightIntention(float Force)
{
    if(!ensure(RightTrack && LeftTrack)) { return; } // pointers protection avoiding crashes

    RightTrack->SetTrackForce(Force);
    LeftTrack->SetTrackForce(-Force);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    /// by not Supper:: calling here, we're replacing the functionality of the method.

    auto AIDirection = MoveVelocity.GetSafeNormal();
    auto TankDirection = GetOwner()->GetActorForwardVector();

    auto ForwardForce = FVector::DotProduct(AIDirection, TankDirection);
    auto RightForce = FVector::CrossProduct(TankDirection, AIDirection).Z;

    MoveForwardIntention(ForwardForce);
    MoveRightIntention(RightForce);
}