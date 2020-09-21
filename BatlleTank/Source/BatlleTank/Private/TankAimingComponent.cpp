// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Rotator.h"

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

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
			auto Time = GetWorld()->GetTimeSeconds();
			DrawDebugLine(GetWorld() , StartLocation, HitLocation, FColor( 0 , 255 , 0 ) , false , 0.f , 0 , 10.f);
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			auto TankName = GetOwner()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("%f Solution for %s found at %s"), Time, *TankName, *AimDirection.ToString())
			MoveBarrel(AimDirection);
			MoveTurret(AimDirection);
		}

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	//Work-out difference between current turret rotation and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - TurretRotator;

	Turret->RotateTurret(DeltaRotator.Yaw);
}