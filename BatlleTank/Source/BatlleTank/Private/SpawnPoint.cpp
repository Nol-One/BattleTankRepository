// Copyright N01 Ltda.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// making sure that the actor is spawned at the right time, then we call "finishing spawning"
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ActorClass, GetComponentTransform());
	if (!ensure(SpawnedActor)) return; // pointer protection to avoid crashes
	
	// attaching the spawned actor to this component, and keeping its transform where it has spawned.
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());

}

