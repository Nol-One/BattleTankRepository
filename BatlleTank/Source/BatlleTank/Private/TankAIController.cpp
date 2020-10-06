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

    if (PlayerTank && ControlledTank)
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

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(InPawn)
    {
        auto PossedTank = Cast<ATank>(GetPawn());
        if (!ensure(PossedTank)) { return; }

        // the event is calling our function in order to do something. This is the other side of the unreals magic.
        PossedTank->ImDead.AddUniqueDynamic(this, &ATankAIController::OnDeath);
    }
}

void ATankAIController::OnDeath()
{
    auto PossedTank = Cast<ATank>(GetPawn());
    PossedTank->DetachFromControllerPendingDestroy();
}
