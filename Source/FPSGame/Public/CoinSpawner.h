// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinSpawner.generated.h"

UCLASS()
class FPSGAME_API ACoinSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: 

	UFUNCTION(Server, Reliable)
	void Server_Spawn();

	UFUNCTION(Server, Reliable)
	void Server_SpawnPickups();


public:
	UPROPERTY(EditAnywhere, Category = "Pickup To Spawn")
	TSubclassOf<class ACoinActor> PickupToSpawn;

	UPROPERTY(EditAnywhere, Category = "Pos Range")
	float MinPosRange;

	UPROPERTY(EditAnywhere, Category = "Pos Range")
	float MaxPosRange;

	FTimerHandle SpawnTimerHandler;

	UPROPERTY(EditAnywhere, Category = "Max Pickups")
	int MaxPickups;

};
