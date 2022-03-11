// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "FPSBlackHole.generated.h"



UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components");
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components");
	USphereComponent* InnerSphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components");
	USphereComponent* OuterSphereComp;

	UPROPERTY(EditAnywhere, Category = "Gameplay");
	float GravityStrength;

	// Apply a radial force towards the black hole center
	void ApplyRadialForceWithinOuterSphere(float Strength);

	// destroy entities get inside the inner sphere
	void DestroyWithinInnerSphere();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
