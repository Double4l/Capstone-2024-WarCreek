// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBombActor.generated.h"

UCLASS()
class FPSGAME_API AFPSBombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBombActor();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
		float ExplodeDelay;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UParticleSystem* ExplosionTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	class UStaticMeshComponent* BombMesh;

	//UPROPERTY(EditDefaultsOnly, Category = "BombActor")
	UPROPERTY(VisibleAnywhere, Category = "BombActor")
		class UBoxComponent* BombBox;
	   
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class URadialForceComponent* RadialForceComp;

	/* Impulse applied to the barrel mesh when it explodes to boost it up a little */
	/*UPROPERTY(EditDefaultsOnly, Category = "FX")
		float ExplosionImpulse;*/

	UFUNCTION(NetMulticast, Reliable)
	void NMC_Explode();

	UFUNCTION()
	void DestroyBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp,
				   AActor* OtherActor, 
				   UPrimitiveComponent* OtherComp, 
				   FVector NormalImpulse, 
				   const FHitResult& Hit);

	void Hold(USkeletalMeshComponent* HoldingComponent, APlayerController* PlayerController);
	void Throw(FVector direction);
};
