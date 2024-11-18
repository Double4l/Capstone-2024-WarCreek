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

	int n = sizeof(SpawnPoints) / sizeof(SpawnPoints[0]);
	std::cout << "Hellooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" + n << std::endl;

	for (int i = 0; i < SpawnPoints.Num(); i++) {
		SpawnPoints[i]->Destroy();
	}

	
}

// Called every frame
void ATargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

