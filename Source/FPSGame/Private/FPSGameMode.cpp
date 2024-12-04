// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacterUE5Character.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "FPSCharacterUE5Character.h"
#include "TargetSpawner.h"
#include "CoinSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "CoinActor.h"
#include "AppleActor.h"
#include "BottleActor.h"
#include "FPSGameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "FPSPlayerState.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
	SpawnPoint = FVector(-800.f, -230.f, 300.f);
}

void AFPSGameMode::BeginPlay()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPSGameMode::StartCountdown, 1.f, true, 5.0);

	Super::BeginPlay();
	StartGame();
}

void AFPSGameMode::StartGame() 
{
	FTimerHandle SpawnHandle;
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AFPSGameMode::SpawnTargets, 1.f, false, 5.0);

	FTimerHandle CoinSpawnHandle;
	GetWorldTimerManager().SetTimer(CoinSpawnHandle, this, &AFPSGameMode::SpawnCoins, 1.f, false, 5.0);

	Minutes = 1;
	Seconds = 0;
}
void AFPSGameMode::StopGame()
{
	TArray<AActor*> CoinActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoinActor::StaticClass(), CoinActors);

	for (int i = 0; i < CoinActors.Num(); i++) {
		CoinActors[i]->Destroy();
	}

	TArray<AActor*> AppleActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAppleActor::StaticClass(), AppleActors);

	for (int i = 0; i < AppleActors.Num(); i++) {
		AppleActors[i]->Destroy();
	}

	TArray<AActor*> BottleActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABottleActor::StaticClass(), BottleActors);

	for (int i = 0; i < BottleActors.Num(); i++) {
		BottleActors[i]->Destroy();
	}


	AFPSGameStateBase* GameState = Cast<AFPSGameStateBase>(GetWorld()->GetGameState());
	GameState->TargetsLeft = 0;

	GameStarted = false;
	StartGame();
}


void AFPSGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);
	SpawnWeapon();
}

void AFPSGameMode::SpawnWeapon()
{
	const float WeaponOffset = 100.f;
	AActor* Weapon = GetWorld()->SpawnActor(WeaponTemplate, &SpawnPoint, &FRotator::ZeroRotator);
	Weapon->SetReplicates(true);
	SpawnPoint.X += WeaponOffset;
}

// Called every frame
void AFPSGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSGameMode::SpawnCoins()
{
	CoinSpawner->Server_SpawnPickups();

}
void AFPSGameMode::SpawnTargets()
{
	GameStarted = true;
	TargetSpawner->Server_SpawnTargets();
}

void AFPSGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	HandleNewPlayer(NewPlayer);
}

void AFPSGameMode::HandleNewPlayer(APlayerController* NewPlayer)
{
	AFPSCharacterUE5Character* Player = Cast<AFPSCharacterUE5Character>(NewPlayer->GetPawn());
	if (Player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, "Character Logged In");
		Player->Server_AssignTeams();
	}
}

void AFPSGameMode::RespawnPlayers() // APlayerController* NewPlayer, int SpawnIndex
{
	AFPSGameStateBase* GameState = Cast<AFPSGameStateBase>(GetWorld()->GetGameState());

	for (int i = 0; i < (GameState->PlayerArray.Num()); i++) {
		APlayerController* NewPlayer = Cast<APlayerController>(GameState->PlayerArray[i]->GetOwner());
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

		APawn* Pawn = SpawnDefaultPawnFor(NewPlayer, PlayerStarts[i]);

		if (Pawn)
		{
			AFPSCharacterUE5Character* Character = Cast<AFPSCharacterUE5Character>(Pawn);
			if (Character)
			{
				NewPlayer->SetPawn(Pawn);
				RestartPlayer(NewPlayer);
			}
		}
	}

}

void AFPSGameMode::StartCountdown()
{
	if (GameStarted) {
		if (Seconds != 0)
		{
			Seconds = Seconds - 1;
		}
		else
		{
			if (Minutes == 0)
			{
				RespawnPlayers();
				StopGame();
			}
			else
			{
				Minutes = Minutes - 1;
				Seconds = 59;
			}
		}
	}
}

