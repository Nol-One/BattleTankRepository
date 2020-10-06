// Copyright N01 Ltda.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UParticleSystemComponent;
class ASprungWheel;

// declaring the events type to be delegated
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UCLASS(hidecategories = ("Cooking", "LOD", "Input", "Rendering", ""))
class BATLLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	public:
		// called by the engine when damage to the actor is dealt
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

		UFUNCTION(BlueprintPure, Category = "Energy")
		float GetEnergyPercent() const;

		// event to be sent when tank is dead
		FDeathEvent ImDead;

	private:
		ATank(); // constructor

		UPROPERTY(VisibleAnywhere, Category = "Energy")   // my understanding of Health Points (HP)
		int EnergyPoints = 100; // sensible default

		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		UStaticMeshComponent* Body;

		UPROPERTY(EditDefaultsOnly, Category = "VFX")
		UParticleSystemComponent* DeathVFX;
};

