// Copyright N01 Ltda.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
    auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
    auto Rotation = GetRelativeRotation().Yaw + RotationChange;

    SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));   
}