// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BottleActor.generated.h"

UCLASS()
class FPSGAME_API ABottleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABottleActor();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class URadialForceComponent* RadialForceComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UParticleSystem* ExplosionTemplate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void DestroyBottle();

	UFUNCTION(NetMulticast, Reliable)
	void NMC_Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

public:
	class ATargetSpawner* GetTargetSpawner();
};
