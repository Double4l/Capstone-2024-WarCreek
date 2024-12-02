// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "FPSGameMode.h"

AFPSGameStateBase::AFPSGameStateBase()
{
    PrimaryActorTick.bCanEverTick = true;
    SetReplicates(true);
}

void AFPSGameStateBase::BeginPlay()
{
    Super::BeginPlay();
}

void AFPSGameStateBase::UpdateTarget()
{
    TargetsLeft -= 1;
    if (TargetsLeft == 0) { // and timer not finished or wtever
       // AFPSGameMode *GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
        //GM->SpawnTargets();
        // Need to be server sided or wont work
    }
}

void AFPSGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AFPSGameStateBase, PlayerOneLoggedIn);
    DOREPLIFETIME(AFPSGameStateBase, PlayerTwoLoggedIn);
    //DOREPLIFETIME(AFPSGameStateBase, PlayerOneScore); // sus
    //DOREPLIFETIME(AFPSGameStateBase, PlayerTwoScore); // sus
    DOREPLIFETIME(AFPSGameStateBase, TargetsLeft); // sus
}

