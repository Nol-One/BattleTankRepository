// Copyright N01 Ltda.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

UTankAimingComponent::UTankAimingComponent()
{
	// this line is here in order to make the tick component actually ticks.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bTargetFound)
	{
		FiringStatus = EFiringStatus::NoTarget;
	}
	else if (bIsBarrelMoving)
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else if (GetWorld()->GetTimeSeconds() - LastFireTime < ReloadTimeSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else
	{
		FiringStatus = EFiringStatus::Ready;
	}
	
}

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
	bTargetFound = UGameplayStatics::SuggestProjectileVelocity
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

		if(bTargetFound)
		{	
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveTurretBarrelTo(AimDirection);
			IsBarrelMoving(AimDirection);
		}
		else if (!bTargetFound)
		{
			bTargetFound = false;
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

void UTankAimingComponent::IsBarrelMoving(FVector AimDirection)
{
	if(Barrel->GetForwardVector().Equals(AimDirection, 0.1f))
	{
		bIsBarrelMoving = false;
	}

	else
	{
		bIsBarrelMoving = true;
	}
	
}

void  UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && Projectile_BP)) {return;} // pointer protection to avoid crashes

	if (FiringStatus == EFiringStatus::Ready)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}
