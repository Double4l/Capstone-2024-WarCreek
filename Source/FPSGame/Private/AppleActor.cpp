// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleActor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "kismet/GameplayStatics.h"
#include "Engine/Engine.h"

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
}

// Called when the game starts or when spawned
void AAppleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAppleActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	NMC_Explode();
}

void AAppleActor::NMC_Explode_Implementation() 
{
	DestroyApple();
}

// Called when the game starts or when spawned
void AAppleActor::DestroyApple()
{
	Destroy();
}

// Called every frame
void AAppleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

