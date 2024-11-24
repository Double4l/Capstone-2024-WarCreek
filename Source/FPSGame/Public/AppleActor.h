// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleActor.generated.h"

UCLASS()
class FPSGAME_API AAppleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void DestroyApple();

	UFUNCTION(NetMulticast, Reliable)
	void NMC_Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
