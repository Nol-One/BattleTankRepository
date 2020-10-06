// Copyright N01 Ltda.

#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
    auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
    auto ElevationUpdate = GetRelativeRotation().Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(ElevationUpdate, MinElevationDegree, MaxElevationDegree);

    SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));   
}