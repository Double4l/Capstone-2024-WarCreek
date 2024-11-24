// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"
#include "BottleActor.h"
#include <iostream>

// Sets default values
ATargetSpawner::ATargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	Server_SpawnTargets();

	//int n = sizeof(SpawnPoints) / sizeof(SpawnPoints[0]);
	//std::cout << "Hellooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" + n << std::endl;

	//for (int i = 0; i < SpawnPoints.Num(); i++) {
	//	SpawnPoints[i]->Destroy();
	//}

	
}

// Spawn implementation
void ATargetSpawner::Server_Spawn_Implementation(AActor *SpawnPoint)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		FVector SpawnPosition = SpawnPoint->GetActorLocation();
		const FRotator SpawnRotation = FRotator(0, 0, 0);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		//World->Spawn
		World->SpawnActor<ABottleActor>(PickupToSpawn, SpawnPosition, SpawnRotation, ActorSpawnParams);
	}
}

void ATargetSpawner::Server_SpawnTargets_Implementation()
{

	for (int i = 0; i < SpawnPoints.Num(); i++) {
		//SpawnPoints[i]->Destroy();
		Server_Spawn(SpawnPoints[i]);
	}
}

// Called every frame
void ATargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

