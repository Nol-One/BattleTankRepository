// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    if (!GetPlayerTank())
    {
        UE_LOG(LogTemp, Error, TEXT("AI didn't find the player"))
    }

    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI is looking at %s"), *GetPlayerTank()->GetName())
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank*  ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}