// Copyright N01 Ltda.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    // needed in order to make the tick actually ticks.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // provided the tracks uses relatively the same axis than the tank body, we get both vectors from it
    auto SlipSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector()); 

    // workout required acceleration (to correct) this frame 
    auto CounterAcceleration = (-SlipSpeed / DeltaTime) * GetRightVector();

    // calculate and apply side-ways (F = m * a)
    auto TankRoot = Cast<UMeshComponent>(GetOwner()->GetRootComponent());
    auto CounterSlipForce = (TankRoot->GetMass() * CounterAcceleration) / 2; // divided by two, hence there's two tracks

    // apply counter force
    TankRoot->AddForce(CounterSlipForce);
}

void UTankTrack::SetTrackForce(float Force)
{
    // TODO clamp input bindings force value to avoid player scaling up the movement speed
    auto ForceApplied = GetForwardVector() * Force * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UMeshComponent>(GetOwner()->GetRootComponent());

    if (ensure(TankRoot))
    {
        TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    }
}   