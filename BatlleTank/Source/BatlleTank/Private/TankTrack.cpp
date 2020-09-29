// Copyright N01 Ltda.

#include "TankTrack.h"

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();

    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // move the tank
    DriveTrack();

    // apply anti-slipping sideways force
    ApplyCounterSlipForce();

    // set force back to zero after using it
    ClampedForce = 0.0f;
}

void UTankTrack::SetTrackForce(float Force)
{
    ClampedForce = FMath::Clamp<float>(ClampedForce + Force, -1.0f, 1.0f);
}   

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * ClampedForce * MaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UMeshComponent>(GetOwner()->GetRootComponent());

    if (ensure(TankRoot))
    {
        TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    }
}

void UTankTrack::ApplyCounterSlipForce()
{
    // workout required acceleration (to correct) this frame
    auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); 
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CounterAcceleration = -SlipSpeed / DeltaTime * GetRightVector();

    // calculate and apply side-ways (F = m * a)
    auto TankRoot = Cast<UMeshComponent>(GetOwner()->GetRootComponent());
    auto CounterSlipForce = (TankRoot->GetMass() * CounterAcceleration) / 2; // divided by two, hence there's two tracks

    // apply counter force
    TankRoot->AddForce(CounterSlipForce);
}



