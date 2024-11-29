// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AFPSPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AFPSPlayerState, PlayerScore);
    DOREPLIFETIME(AFPSPlayerState, HighestScore);
}