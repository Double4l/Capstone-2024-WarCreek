// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinActor.h"
#include "FPSCharacterUE5Character.h"
#include "FPSGameStateBase.h"
#include "FPSPlayerState.h"

// Sets default values
ACoinActor::ACoinActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ACoinActor::BeginPlay()
{
	Super::BeginPlay();
	
	//WE only want to detect Overlaps on the Server
	if (GetLocalRole() == ROLE_Authority)
	{
		OnActorBeginOverlap.AddDynamic(this, &ACoinActor::OnOverlapBegin);
	}
}

// Called every frame
void ACoinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACoinActor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AFPSCharacterUE5Character* Player = Cast<AFPSCharacterUE5Character>(OtherActor);
	ACoinActor* Pickup = Cast<ACoinActor>(OverlappedActor);

	// Checks If Character exist
	if (Player != nullptr)
	{
		// Checks If Pickup exist
		if (Pickup != nullptr) 
		{
			UWorld* World = GetWorld();
			// Checks If World Exist

			if (World != nullptr) 
			{
				// destroy actor

				AFPSGameStateBase *GS = Player->GetGameState();
				if (GS) 
				{
					AFPSPlayerState *PlayerState = Player->GetCharacterPlayerState();
					if (PlayerState) 
					{
						PlayerState->PlayerScore += 1;
						Destroy();
					}
				}
			}
		}
	}

}



