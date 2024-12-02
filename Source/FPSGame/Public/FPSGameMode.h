// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AActor> WeaponTemplate;

	UPROPERTY(BlueprintReadOnly)
		int Minutes = 2;

	UPROPERTY(BlueprintReadOnly)
		int Seconds = 0;

	void StartCountdown();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	int Amount;

	protected:
		virtual void BeginPlay() override;
		virtual void PostLogin(APlayerController* PlayerController);

		virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
		void HandleNewPlayer(APlayerController* NewPlayer);

		void SpawnWeapon();
		void SpawnTargets();
		void HandleNewPlayer();
		void RespawnPlayers();
		void StartGame();

		FVector SpawnPoint;

};



