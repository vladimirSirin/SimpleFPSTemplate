// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components\BoxComponent.h"
#include "Components\DecalComponent.h"
#include "FPSCharacter.h"
#include <FPSGame/Public/FPSGameMode.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Setup the box component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;

	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetBoxExtent(FVector(200.0f));

	BoxComp->SetHiddenInGame(false);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->SetupAttachment(RootComponent);

	DecalComp->DecalSize = FVector(200.0f);

}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AFPSCharacter* PlayerPawn = Cast<AFPSCharacter>(OtherActor);

	if (PlayerPawn == nullptr)
	{
		return;
	}

	if (!PlayerPawn->bIsCarringObjective)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ObjectiveMissingSound, GetActorLocation());
	}

	if (PlayerPawn->bIsCarringObjective)
	{
		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		
		if (GM)
		{
			GM->CompleteMission(PlayerPawn, true);
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Player has entered the extracton zone."));
	
}


