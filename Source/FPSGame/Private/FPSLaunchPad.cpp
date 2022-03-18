// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "Components\BoxComponent.h"
#include <FPSGame/Public/FPSCharacter.h>
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup the Static mesh comp and box mesh using for overlapping
	SMComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SMComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SMComp->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = SMComp;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlapping Box"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(100.0F));
	OverlapComp->SetHiddenInGame(false);
	OverlapComp->SetupAttachment(RootComponent);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);

}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSLaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
	{
		return;
	}
	
	AFPSCharacter* PlayerPawn = Cast<AFPSCharacter>(OtherActor);
	
	if (PlayerPawn)
	{
		PlayLaunchFX();
		PlayerPawn->LaunchCharacter(LaunchStrength, true, true);
	}
	else if (OtherComp)
	{
		UE_LOG(LogTemp, Log, TEXT("Overlapping with an non-pawn actor!"))
		PlayLaunchFX();
		OtherComp->AddForce(LaunchStrength*OtherComp->GetMass(), FName(), false);
	}
	



}

void AFPSLaunchPad::PlayLaunchFX()
{

	if (LaunchFX)
	{
		UParticleSystemComponent* SpawnedFX = UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
		SpawnedFX->SetRelativeScale3D(LaunchFXsize);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("MISSING FX, SET IT UP IN DEFAULTS!"))
	}

}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

