// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState: uint8
{
	Relax,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY()
	FTimerHandle NoiseAlarmTimer;
	
	UPROPERTY()
	FRotator OriginalRotation;

	UPROPERTY()
	EAIState CurrentAIState;

	UFUNCTION()
	void ResetRotationToOriginal();

	UFUNCTION()
	void OnSeenPawn(APawn* SeenPawn);

	UFUNCTION()
	void OnHeardNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void LookAtNoiseLocation(FVector Location);

	UFUNCTION()
	void SetAIState(EAIState state);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnAIstateSet(EAIState state);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
