// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSpawner.h"
#include "CoinActor.h"


// Sets default values
ACoinSpawner::ACoinSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ACoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoinSpawner::Server_Spawn_Implementation()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		float X = FMath::RandRange(MinPosRange, MaxPosRange);
		float Y = FMath::RandRange(MinPosRange, MaxPosRange);

		FVector SpawnPosition = FVector(X, Y, 0);
		const FRotator SpawnRotation = FRotator(0, 0, 0);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<ACoinActor>(PickupToSpawn, SpawnPosition, SpawnRotation, ActorSpawnParams);
	}
}
