// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto ControlledTank =  Cast<ATank>(GetPawn());
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (ensure(PlayerTank && ControlledTank))
    {
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        ControlledTank->Fire();

        MoveToActor(PlayerTank, StopDistance);
    }
}

