// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
    AFPSGameStateBase();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (ClampMin = 0), Replicated)
    int PlayerOneScore;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (ClampMin = 0), Replicated)
    int PlayerTwoScore;

public:
    UPROPERTY(EditAnywhere, Replicated)
    bool PlayerOneLoggedIn;

    UPROPERTY(EditAnywhere, Replicated)
    bool PlayerTwoLoggedIn;

protected:
    virtual void BeginPlay() override;
	
};
