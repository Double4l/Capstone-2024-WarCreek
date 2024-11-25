// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleActor.h"

// Sets default values
AAppleActor::AAppleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAppleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAppleActor::NMC_Explode_Implementation() 
{

}

// Called when the game starts or when spawned
void AAppleActor::DestroyApple()
{
	Destroy();
}

// Called every frame
void AAppleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

