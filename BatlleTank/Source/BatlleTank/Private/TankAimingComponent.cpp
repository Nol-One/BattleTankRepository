// Copyright N01 Ltda.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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

void  UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && Projectile_BP)) {return;} // pointer protection to avoid crashes

	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeSeconds;

	if (bIsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::MoveTurretBarrelTo(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) {return;} // protecting pointers to avoid crashes

	// work-out difference between current barrel rotation and aim rotator
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}