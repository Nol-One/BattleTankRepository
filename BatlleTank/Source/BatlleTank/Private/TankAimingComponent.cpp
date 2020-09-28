// Copyright N01 Ltda.

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

void UTankAimingComponent::Initialise (UTankTurret* SetTurret, UTankBarrel* SetBarrel)
{
	Barrel = SetBarrel;
	Turret = SetTurret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; } // protecting pointers to avoid crashes

	FVector OutLaunchVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bSuccessfulAimCalculation = UGameplayStatics::SuggestProjectileVelocity
	(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		if(bSuccessfulAimCalculation)
		{	
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveTurretBarrelTo(AimDirection);
		}

}

void UTankAimingComponent::MoveTurretBarrelTo(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) {return;} // protecting pointers to avoid crashes

	//Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}