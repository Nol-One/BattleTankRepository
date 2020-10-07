// Copyright N01 Ltda.

#pragma once
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATLLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:
	AActor* GetSpawnedActor() const {return SpawnedActor;}

private:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "ActorToSpawn")
	TSubclassOf<AActor> ActorClass;

	AActor* SpawnedActor = nullptr;
};
