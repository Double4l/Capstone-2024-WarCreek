// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleActor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "FPSGameStateBase.h"
#include "FPSCharacterUE5Character.h"
#include "FPSPlayerState.h"
#include "FPSProjectile.h"

// Sets default values
AAppleActor::AAppleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComppppppppp"));
	SphereComp->SetCollisionProfileName("BlockAllDynamic");
	SphereComp->OnComponentHit.AddDynamic(this, &AAppleActor::OnHit);	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	//CALL SetWalkableSlopeOverride() on BombBox passing in WalkableSlope_Unwalkable, 0.f)
	SphereComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//SET CanCharacterStepUpOn on BombBox to ECB_No
	SphereComp->CanCharacterStepUpOn = ECB_No;

	//SET BombBox as the RootComponent
	RootComponent = SphereComp;

	//CREATE the RadialForceComp
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	//ATTACH the RadialForceComp to the RootComponent
	RadialForceComp->SetupAttachment(RootComponent);
	//SET the RadialForceComp's Radius to 250 or a value of your choice
	RadialForceComp->Radius = 250;
	//SET the RadialForceComp's bImpulseVelChange property to true
	RadialForceComp->bImpulseVelChange = true;
	//SET the RadialForceComp's bAutoActivate property to false. This will prevent the RadialForceComp from ticking and we will only use FireImpulse() instead
	RadialForceComp->bAutoActivate = false; // Prevent component from ticking, and only use FireImpulse() instead
	//SET the RadialForceComp's bIgnoreOwningActor property to true (ignoring self)
	RadialForceComp->bIgnoreOwningActor = true; // ignore self

	//CALL SetSimulatePhysics() on the BombBox to true
	SphereComp->SetSimulatePhysics(true);
	//CALL SetCollisionEnabled() on BombBox and enable it to respond to Queries and Physics Collision
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//CALL SetCollisionResponseToChannel() on the BombBox, Make it Ignore the Pawn
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); //Was ECR_Ignore

	SphereComp->SetIsReplicated(true);
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AAppleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAppleActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	AFPSProjectile* Projectile = Cast<AFPSProjectile>(OtherActor);
	// Checks If Character exist

	if (Projectile != nullptr)
	{
		UWorld* World = GetWorld();
		// Checks If World Exist

		if (World != nullptr)
		{
			// destroy actor

			AFPSCharacterUE5Character* Player = Projectile->CharacterFired;
			if (Player) 
			{
				AFPSGameStateBase* GS = Player->GetGameState();

				if (GS)
				{
					AFPSPlayerState* PlayerState = Player->GetCharacterPlayerState();
					if (PlayerState)
					{
						PlayerState->PlayerScore += 5;
						NMC_Explode();
					}
				}
			}
		}
	}
}

void AAppleActor::NMC_Explode_Implementation() 
{
	//SPAWN the ExplosionTemplate using UGameplayStatics::SpawnEmitterAtLocation(....)
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());


	// Blast away nearby physics actors by Calling FireImpulse() on the Radial Force Component
	RadialForceComp->FireImpulse();

	DestroyApple();
}

// Called when the game starts or when spawned
void AAppleActor::DestroyApple()
{
	AFPSGameStateBase* GameState = Cast<AFPSGameStateBase>(GetWorld()->GetGameState());
	//GameState->TargetsLeft -= 1;
	GameState->UpdateTarget();
	Destroy();
}

// Called every frame
void AAppleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

