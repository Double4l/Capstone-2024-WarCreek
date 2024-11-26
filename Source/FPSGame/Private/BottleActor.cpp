// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleActor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
ABottleActor::ABottleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set up a notification for when this component hits something blocking

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsullllllllleComp"));
	CapsuleComp->SetCollisionProfileName("BlockAllDynamic");
	CapsuleComp->OnComponentHit.AddDynamic(this, &ABottleActor::OnHit);	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	//CALL SetWalkableSlopeOverride() on BombBox passing in WalkableSlope_Unwalkable, 0.f)
	CapsuleComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//SET CanCharacterStepUpOn on BombBox to ECB_No
	CapsuleComp->CanCharacterStepUpOn = ECB_No;

	//SET BombBox as the RootComponent
	RootComponent = CapsuleComp;

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

}

// Called when the game starts or when spawned
void ABottleActor::BeginPlay()
{
	Super::BeginPlay();

	//WE only want to detect Overlaps on the Server
	if (GetLocalRole() == ROLE_Authority)
	{
		OnActorBeginOverlap.AddDynamic(this, &ABottleActor::OnOverlapBegin);
	}
}

void ABottleActor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

}

void ABottleActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	NMC_Explode();
}

void ABottleActor::NMC_Explode_Implementation()
{
	DestroyBottle();
}

// Called when the game starts or when spawned
void ABottleActor::DestroyBottle()
{
	Destroy();
}

// Called every frame
void ABottleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

