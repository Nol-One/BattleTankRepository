// Copyright N01 Ltda.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto ControlledTank =  Cast<ATank>(GetPawn());
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (ensure(PlayerTank && ControlledTank))
    {
        auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

        AimingComponent->AimAt(PlayerTank->GetActorLocation());

        MoveToActor(PlayerTank, StopDistance);

        if (AimingComponent->GetFiringStatus() == EFiringStatus::Ready)
        {
            AimingComponent->Fire();
        }  
    }
}

