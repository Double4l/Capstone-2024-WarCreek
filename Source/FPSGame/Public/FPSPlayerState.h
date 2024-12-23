// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Replicated)
	int PlayerScore;

	UPROPERTY(EditAnywhere, Replicated)
	int PlayerTeam;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int PlayerHighestScore;


};
