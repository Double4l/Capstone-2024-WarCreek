// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacterUE5Character.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "FPSCharacterUE5Character.h"

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
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPSGameMode::StartCountdown, 1.f, true, 0.0);
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

void AFPSGameMode::SpawnTargets()
{
	
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
		//Player->Server_AssignTeams();
	}
}
void AFPSGameMode::RespawnPlayers()
{

}

void AFPSGameMode::StartCountdown()
{
	if (Seconds != 0) 
	{
		Seconds = Seconds - 1;
	}
	else 
	{
		if (Minutes == 0) 
		{
			// Do some stuff when timer has finished
		}
		else
		{
			Minutes = Minutes - 1;
			Seconds = 59;
		}
	}
}

