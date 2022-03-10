// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Define a mesh, a sphere and and FX
	UPROPERTY(VisibleAnywhere, category = "Components");
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, category = "Components");
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "VisualFX");
	UParticleSystem* PickupFX;

	// Play the set FX
	void PlayEffect();

	// Call when overlap
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


public:	
	//

};
