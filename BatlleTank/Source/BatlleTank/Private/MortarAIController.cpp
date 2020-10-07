// Copyright N01 Ltda.

#include "MortarAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"


void AMortarAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto ControlledMortar =  GetPawn();
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (PlayerTank && ControlledMortar)
    {
        auto AimingComponent = ControlledMortar->FindComponentByClass<UTankAimingComponent>();

        AimingComponent->AimAt(PlayerTank->GetActorLocation());

        if (AimingComponent->GetFiringStatus() == EFiringStatus::Ready)
        {
            AimingComponent->Fire();
        }  
    }
}


