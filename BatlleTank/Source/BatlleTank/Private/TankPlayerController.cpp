// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

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
    if (!GetControlledTank()) { return; }
}

