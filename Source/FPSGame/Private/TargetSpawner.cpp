// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"
#include "BottleActor.h"
#include <iostream>
#include "FPSGameStateBase.h"

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
}

// Spawn implementation
void ATargetSpawner::Server_Spawn_Implementation(AActor *SpawnPoint)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		FVector SpawnPosition = SpawnPoint->GetActorLocation() +  FVector(0, 0, 50);;
		const FRotator SpawnRotation = FRotator(0, 0, 0);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		//World->Spawn

		int position = FMath::RandRange(0, PickupTypes.Num() - 1);
		World->SpawnActor<AActor>(PickupTypes[position], SpawnPosition, SpawnRotation, ActorSpawnParams);
	}
}

void ATargetSpawner::Server_SpawnTargets_Implementation()
{

	for (int i = 0; i < SpawnPoints.Num(); i++) {
		//AActor Target = PickupTypes[1];
		Server_Spawn(SpawnPoints[i]);
	}

	AFPSGameStateBase* GameState = Cast<AFPSGameStateBase>(GetWorld()->GetGameState());
	GameState->TargetsLeft = SpawnPoints.Num();
}

// Called every frame
void ATargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



//int n = sizeof(SpawnPoints) / sizeof(SpawnPoints[0]);
	//std::cout << "Hellooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" + n << std::endl;

	//for (int i = 0; i < SpawnPoints.Num(); i++) {
	//	SpawnPoints[i]->Destroy();
	//}