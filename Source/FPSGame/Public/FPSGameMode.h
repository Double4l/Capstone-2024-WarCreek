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
		int Minutes = 10;

	UPROPERTY(BlueprintReadOnly)
		int Seconds = 5;

	void StartCountdown();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	protected:
		virtual void BeginPlay() override;
		virtual void PostLogin(APlayerController* PlayerController);

		void SpawnWeapon();
		void SpawnTargets();
		void HandleNewPlayer();
		void RespawnPlayers();

		FVector SpawnPoint;

};



