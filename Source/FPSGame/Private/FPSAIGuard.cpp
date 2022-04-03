// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "FPSGameMode.h"
#include <AIController.h>
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeenPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHeardNoise);

	OriginalRotation = GetActorRotation();
	CurrentAIState = EAIState::Relax;

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	if (!GuardPatrolPoints.IsEmpty())
	{
		CurrentWaypoint = GuardPatrolPoints[0];
	}
}

void AFPSAIGuard::ResetRotationToOriginal()
{
	SetActorRotation(OriginalRotation);
	SetAIState(EAIState::Relax);
}

// Called whens seeing a player pawn
void AFPSAIGuard::OnSeenPawn(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 10.0f);

	SetAIState(EAIState::Alerted);
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	GM->CompleteMission(SeenPawn, false);
	
}

void AFPSAIGuard::OnHeardNoise(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	SetAIState(EAIState::Suspicious);
	
	GetWorld()->GetTimerManager().ClearTimer(NoiseAlarmTimer);

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.0f);
	LookAtNoiseLocation(Location);

	GetWorld()->GetTimerManager().SetTimer(NoiseAlarmTimer, this, &AFPSAIGuard::ResetRotationToOriginal, 4.0f, false);

}


// Look at noise location.
void AFPSAIGuard::LookAtNoiseLocation(FVector Location)
{
	FVector direction = Location - GetActorLocation();
	direction.Normalize();
	FRotator LookAtRotation = direction.Rotation();
	LookAtRotation.Pitch = 0.0f;
	LookAtRotation.Roll = 0.0f;

	FRotator LerpRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 25.0f);

	SetActorRotation(LerpRotation);
}




void AFPSAIGuard::SetAIState(EAIState state)
{
	if (CurrentAIState == state)
	{
		return;
	}
	CurrentAIState = state;
	OnRep_GuardState();
}

void AFPSAIGuard::OnRep_GuardState()
{
	OnAIstateSet(CurrentAIState);
}

ATargetPoint* AFPSAIGuard::GetNextWaypoint(TArray<ATargetPoint*> PatrolPoints, ATargetPoint* Waypoint)
{
	if (PatrolPoints.Num() == 0 || CurrentWaypoint == nullptr)
	{
		return nullptr;
	}

	int Currentindex = PatrolPoints.Find(CurrentWaypoint);
	

	if ((Currentindex + 1) < PatrolPoints.Num())
	{
		return PatrolPoints[Currentindex+1];
	}
	else
	{
		return PatrolPoints[0];
	}
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AFPSAIGuard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGuard, CurrentAIState);
}


