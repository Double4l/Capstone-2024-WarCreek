// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCharacterUE5Character.h"
#include "FPSBombActor.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "BombDamageType.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSGameStateBase.h"
#include "FPSGameMode.h"
#include "FPSPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"


//////////////////////////////////////////////////////////////////////////
// AFPSCharacterUE5Character

AFPSCharacterUE5Character::AFPSCharacterUE5Character()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
		// Create a gun mesh component
	BombGripMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_BombGrip"));
	BombGripMeshComponent->CastShadow = false;
	BombGripMeshComponent->SetupAttachment(Mesh1P, "BombSocket");

	OnTakeAnyDamage.AddDynamic(this, &AFPSCharacterUE5Character::TakeAnyDamage);

	//SET HeldBomb to null
	HeldBomb = nullptr;
	IsAbleToFire = true;

	SetReplicates(true);
	SetReplicateMovement(true);

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void AFPSCharacterUE5Character::Tick(float dt)
{
	Super::Tick(dt);

	FRotator NewRotation = FirstPersonCameraComponent->GetRelativeRotation();
	NewRotation.Pitch = RemoteViewPitch * 360.0f / 255.0f;

	FirstPersonCameraComponent->SetRelativeRotation(NewRotation);

	Super::Tick(dt);

	if (GetCharacterPlayerState())
	{
		UKismetSystemLibrary::DrawDebugString(this, FVector(0.f, 0.f, -10.f), "Score:" + FString::FromInt(GetCharacterPlayerState()->PlayerScore), this, FLinearColor::Green);
		UKismetSystemLibrary::DrawDebugString(this, FVector(0.f, 0.f, -20.f), "Highest Score: " + FString::FromInt(GetCharacterPlayerState()->PlayerHighestScore), this, FLinearColor::Yellow);

		//if (GetLocalRole() == ROLE_AutonomousProxy || GetLocalRole() == ROLE_Authority)
		//{
			//UKismetSystemLibrary::DrawDebugString(this, FVector(0.f, 0.f, -40.f), ":PlayerController - " + GetController()->GetName(), this, FLinearColor::Yellow);

			//UKismetSystemLibrary::DrawDebugString(this, FVector(0.f, 0.f, -60.f), ":Pawn Class - " + GetName(), this, FLinearColor::Yellow);
		//}
	}
}
void AFPSCharacterUE5Character::Server_AssignTeams_Implementation()
{
	if (HasAuthority())
	{
		if (GetGameState())

		{
			if (GetCharacterPlayerState())
			{
				if (GetGameState()->PlayerOneLoggedIn == false)
				{
					GetCharacterPlayerState()->PlayerTeam = 1;
					GetGameState()->PlayerOneLoggedIn = true;
				}
				else if (GetGameState()->PlayerTwoLoggedIn == false)
				{
					GetCharacterPlayerState()->PlayerTeam = 2;
					GetGameState()->PlayerTwoLoggedIn = true;
				}
			}
		}
	}
}

void AFPSCharacterUE5Character::Server_Respawn_Implementation() 
{
	AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	AFPSGameStateBase* GameState = Cast<AFPSGameStateBase>(GetWorld()->GetGameState());

	if (GameMode)
	{
		//GameMode->RespawnPlayers(Cast<APlayerController>(GetController()), GetCharacterPlayerState()->PlayerTeam);
		//Destroy();
	}
}


void AFPSCharacterUE5Character::BeginPlay()
{
	// Call the base class  / 
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//FTimerHandle DelayHandle;
	//GetWorldTimerManager().SetTimer(DelayHandle, this, &AFPSCharacterUE5Character::SetPlayerColor, 1.0f, false);

	//SetPlayerColor();
}

void AFPSCharacterUE5Character::TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Damage Received - " + FString::FromInt(Damage) + " Instigated By: " + InstigatedBy->GetName());

	const UBombDamageType* damageType = Cast<UBombDamageType>(DamageType);
	if (damageType)
	{
		GetCapsuleComponent()->SetSimulatePhysics(false);
		DisableInput(nullptr);
		SetHasRifle(false);
		IsAbleToFire = false;
	}
}

AFPSGameMode* AFPSCharacterUE5Character::GetGameMode()
{
	return Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
}

AFPSPlayerState* AFPSCharacterUE5Character::GetCharacterPlayerState()
{
	return Cast<AFPSPlayerState>(GetPlayerState());
}

AFPSGameStateBase* AFPSCharacterUE5Character::GetGameState()
{
	return Cast<AFPSGameStateBase>(GetWorld()->GetGameState());
}

void AFPSCharacterUE5Character::StartSprint()
{
	UWorld* World = GetWorld();

	//AFPSGameStateBase* GS = Cast<AFPSGameStateBase>(World->GetGameState());
	//GS->TargetsLeft = 100;

	//AFPSGameMode* GM = GetGameMode();
	//GM->Amount = 10;

	//AFPSPlayerState* PS = GetCharacterPlayerState();
	//PS->PlayerScore = 100;

	//GS->TargetsLeft = 100;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
}

void AFPSCharacterUE5Character::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void AFPSCharacterUE5Character::SetPlayerColor()
{
	//NMC_SetPlayerColor(GetGameState()->PlayerOneMaterial);
}

void AFPSCharacterUE5Character::NMC_SetPlayerColor_Implementation(UMaterialInterface* NewMaterial)
{
	//GetMesh()->SetMaterial(0, NewMaterial);
}


void AFPSCharacterUE5Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Sprinting 
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AFPSCharacterUE5Character::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFPSCharacterUE5Character::StopSprint);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacterUE5Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacterUE5Character::Look);

		EnhancedInputComponent->BindAction(BombAction, ETriggerEvent::Triggered, this, &AFPSCharacterUE5Character::PickupBomb);
		EnhancedInputComponent->BindAction(BombAction, ETriggerEvent::Completed, this, &AFPSCharacterUE5Character::Server_ThrowBomb);
	}
}

void AFPSCharacterUE5Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSCharacterUE5Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSCharacterUE5Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AFPSCharacterUE5Character::GetHasRifle()
{
	return bHasRifle;
}

void AFPSCharacterUE5Character::PickupBomb()
{
	//if (HeldBomb)
		//return;

	//Ray Cast to check if a Actor is hit by a raycast
	AActor* PickedActor = RayCastGetActor();
	//IF a Actor has been detected/hit
	if (PickedActor)
	{
		//Check if it is a AFPSBombActor by doing a cast
		AFPSBombActor* bomb = Cast<AFPSBombActor>(PickedActor);
		//IF it is a AFPSBombActor

		if (bomb)
		{
			//SET HeldBomb to the hit bomb
			Server_PickupBomb(bomb);
		}
	}
}

void AFPSCharacterUE5Character::Server_PickupBomb_Implementation(AFPSBombActor* bomb)
{
	if (HeldBomb)
		return;

	HeldBomb = bomb;
	//CALL Hold on the bomb passing in GunMeshComponent, we will attach it to the Gun

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	bomb->Hold(BombGripMeshComponent, PlayerController);
}

void AFPSCharacterUE5Character::Server_ThrowBomb_Implementation()
{
	//IF we have a HeldBomb
	if (HeldBomb)
	{
		//Throw the Held Bomb passing in the Camera's Forward Vector
		HeldBomb->Throw(GetActorRotation().Vector());
		HeldBomb = nullptr;
	}
	//ENDIF
}

AActor* AFPSCharacterUE5Character::RayCastGetActor()
{
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller because we don't want bots to grab the use object and we need a controller for the GetPlayerViewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		//World->LineTraceSingleByObjectType(Hit, StartTrace, EndTrace, ObjectTypeQuery1, TraceParams); // simple trace function  ECC_PhysicsBody
		World->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_PhysicsBody, TraceParams); // simple trace function  ECC_PhysicsBody
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1.f);
		return Hit.GetActor();
	}
	return nullptr;
}

void AFPSCharacterUE5Character::SetupRay(FVector& StartTrace, FVector& Direction, FVector& EndTrace)
{
	FVector CamLoc;
	FRotator CamRot;

	Controller->GetPlayerViewPoint(CamLoc, CamRot); // Get the camera position and rotation

	StartTrace = CamLoc; // trace start is the camera location
	Direction = CamRot.Vector();
	EndTrace = StartTrace + Direction * 300;
}