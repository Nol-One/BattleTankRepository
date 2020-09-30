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

    ApplyCounterSlipForce();
}

void UTankTrack::SetTrackForce(float Force)
{
    ClampedForce = FMath::Clamp<float>(ClampedForce + Force, -1.0f, 1.0f);

    auto ForceApplied = GetForwardVector() * ClampedForce * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UMeshComponent>(GetOwner()->GetRootComponent());

    if (ensure(TankRoot))
    {
        TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
        ClampedForce = 0.0f;
    }

}   

void UTankTrack::ApplyCounterSlipForce()
{
    // workout required acceleration (to correct) this frame 
    auto SlipSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector()); 
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CounterAcceleration = (-SlipSpeed / DeltaTime) * GetRightVector();

    // calculate and apply side-ways (F = m * a)
    auto TankRoot = Cast<UMeshComponent>(GetOwner()->GetRootComponent());
    auto CounterSlipForce = (TankRoot->GetMass() * CounterAcceleration) / 2; // divided by two, hence there's two tracks

    // apply counter force
    TankRoot->AddForce(CounterSlipForce);
}



