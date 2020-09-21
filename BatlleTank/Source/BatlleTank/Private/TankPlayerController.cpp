// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "CoreMinimal.h"
#include "Tank.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/PlayerCameraManager.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (!GetControlledTank())
    {
        UE_LOG(LogTemp, Error, TEXT("Player is NOT controlling a Tank"))
    }

    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is controlling %s"), *GetControlledTank()->GetName())
    }
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
    if (!GetControlledTank()) {return;}

    FHitResult Hit;
    if (CrosshairRaycast(Hit))
    {
        FVector HitLocation = Hit.Location;
        GetControlledTank()->AimAt(HitLocation);
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
    if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, FCollisionQueryParams(FName(TEXT("")), false, GetOwner())))
    {
        return true;
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor( 0 , 255 , 0 ) , false , 0.f , 0 , 5.f);
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
