// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleActor.h"

// Sets default values
ABottleActor::ABottleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABottleActor::BeginPlay()
{
	Super::BeginPlay();

	//WE only want to detect Overlaps on the Server
	if (GetLocalRole() == ROLE_Authority)
	{
		OnActorBeginOverlap.AddDynamic(this, &ABottleActor::OnOverlapBegin);
	}
}

void ABottleActor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

}

void ABottleActor::NMC_Explode_Implementation()
{

}

// Called when the game starts or when spawned
void ABottleActor::DestroyBottle()
{
	Destroy();
}

// Called every frame
void ABottleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

