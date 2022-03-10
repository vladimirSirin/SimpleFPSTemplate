// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup a static mesh component for the black hole centre
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComp;
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Setup the inner and outer sphere, inner is for destroy actors, outer is for applying the force
	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
	InnerSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InnerSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	InnerSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	InnerSphereComp->SetupAttachment(MeshComp);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComponent"));
	OuterSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OuterSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OuterSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	OuterSphereComp->SetupAttachment(MeshComp);


}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

