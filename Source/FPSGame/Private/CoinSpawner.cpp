// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSpawner.h"
#include "CoinActor.h"
#include "FPSGameMode.h"


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
	Server_AssignToGameMode();
}

// Called every frame
void ACoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoinSpawner::Server_AssignToGameMode_Implementation()
{
	AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->CoinSpawner = this;
}


// Spawn implementation
void ACoinSpawner::Server_Spawn_Implementation()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		float X = FMath::RandRange(MinPosRange, MaxPosRange);
		float Y = FMath::RandRange(MinPosRange, MaxPosRange);

		FVector SpawnPosition = FVector(X, Y, 300);
		const FRotator SpawnRotation = FRotator(0, 0, 0);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		ACoinActor *CoinActor = World->SpawnActor<ACoinActor>(PickupToSpawn, SpawnPosition, SpawnRotation, ActorSpawnParams);
		Coins.Add(CoinActor);
	}
}

void ACoinSpawner::Server_SpawnPickups_Implementation()
{

	for (int i = 0; i < MaxPickups; i++) // MaxPickups
	{
		Server_Spawn();
	}

}