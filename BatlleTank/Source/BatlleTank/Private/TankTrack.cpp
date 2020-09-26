
#include "TankTrack.h"
#include "CoreMinimal.h"

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