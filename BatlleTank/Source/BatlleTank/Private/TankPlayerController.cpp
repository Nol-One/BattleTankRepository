// Copyright N01 Ltda.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Components/PrimitiveComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto TankAimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

    FoundAimingComponent(TankAimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!ensure(GetControlledTank())) {return;}

    FHitResult Hit;
    if (CrosshairRaycast(Hit))
    {
        FVector HitLocation = Hit.Location;
        GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
    }
}

bool ATankPlayerController::CrosshairRaycast(FHitResult& Hit)
{
    //OUT parameter reference
    FVector AimDirection;
    
    //parameter to be used in raycast
    GetCrosshairVector(AimDirection);
    
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (AimDirection*Reach);

    // ray cast a line into the world that looks for anything visible, excluding skybox
    if 
    (   
        GetWorld()->LineTraceSingleByChannel
        (
            Hit,
            StartLocation,
            EndLocation,
            ECC_Visibility,
            FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
        )
    )
    
    {
        return true;
    }

    return false;
    Hit.Location = FVector (0); //in case the ray-cast fail
}

bool ATankPlayerController::GetCrosshairVector(FVector& AimDirection) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    //calculating the crosshair location as a 2D vector and using as OUT parameter reference
    auto CrosshairLocation = FVector2D (CrosshairXLocation*ViewportSizeX, CrosshairYLocation*ViewportSizeY); 

    //OUT parameters
    FVector WorldLocation; //discarded, although needed as method parameter
    //transforming the 2D crosshair vector into 3D to be used in raycast
	return DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, WorldLocation, AimDirection);
}
