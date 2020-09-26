
#include "Tank.h"
#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; } // protecting pointers to avoid crashes

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void  ATank::Fire()
{
	if (!ensure(Barrel)) {return;} // pointer protection to avoid crashes

	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeSeconds;

	if (bIsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}