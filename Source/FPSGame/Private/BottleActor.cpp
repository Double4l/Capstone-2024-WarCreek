// Fill out your copyright notice in the Description page of Project Settings.


#include "BottleActor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABottleActor::ABottleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set up a notification for when this component hits something blocking

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

void ABottleActor::NMC_Explode_Implementation()
{

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

