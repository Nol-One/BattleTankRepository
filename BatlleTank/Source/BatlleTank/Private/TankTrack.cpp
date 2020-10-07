// Copyright N01 Ltda.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

void UTankTrack::SetTrackForce(float Force)
{
    auto ClampedForce = FMath::Clamp<float>(Force, -1.0f, 1.0f);
    AddTrackForce(ClampedForce);
}   

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
    TArray<ASprungWheel*> ResultArray;
    TArray<USceneComponent*> Children; // spawn points array
    GetChildrenComponents(true, Children);

    for(USceneComponent* Child : Children) // Child type must be equivalent to the spawn point array (children)
    {
        auto SpawnPoint = Cast<USpawnPoint>(Child);
        if (!SpawnPoint) continue;

        auto SprungWheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
        if (!SprungWheel) continue;

        ResultArray.Add(SprungWheel);
    }

    return ResultArray;
}

void UTankTrack::AddTrackForce(float ClampedForce)
{
    auto ForceApplied = ClampedForce * MaxDrivingForce;

    auto Wheels = GetWheels();

    auto ForcePerWheel = ForceApplied / Wheels.Num();

    for (ASprungWheel* Wheel : Wheels)
    {
        Wheel->AddDrivingForce(ForcePerWheel);
    }
}





