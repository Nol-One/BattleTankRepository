// Copyright N01 Ltda.

#include "Tank.h"
#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"

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