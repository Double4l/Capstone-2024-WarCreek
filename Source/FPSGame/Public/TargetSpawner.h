// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

UCLASS()
class FPSGAME_API ATargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere)
	int NumberOfTargets;

	UPROPERTY(EditAnywhere, Category = "Spawn Points")
	TArray<AActor *> SpawnPoints;

	//UPROPERTY(EditAnywhere, Category = "Targets")
	//TArray<AAple

	//TArray <AApleActor* > Apples;
	TArray <ABottleActor* > Bottles;

public:
	UPROPERTY(EditAnywhere, Category = "Pickup To Spawn")
	TSubclassOf<class AActor> PickupToSpawn;

	UPROPERTY(EditAnywhere, Category = "Pickup Types")
	TArray<TSubclassOf<class AActor>>  PickupTypes;

	UFUNCTION(Server, Reliable)
	void Server_Spawn(AActor *SpawnPoint);

	UFUNCTION(Server, Reliable)
	void Server_AssignToGameState();

	UFUNCTION(Server, Reliable)
	void Server_SpawnTargets();

};
