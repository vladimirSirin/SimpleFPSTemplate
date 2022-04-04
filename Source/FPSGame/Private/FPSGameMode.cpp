// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* PawnInstigator, bool bIsMissionScucess)
{
	if (PawnInstigator == nullptr)
	{
		return;
	}
	
	APlayerController* PlayerController = Cast<APlayerController>(PawnInstigator->GetController());

	if (PlayerController)
	{
		if (SpectatingViewingTarget)
		{
			AActor* ViewingTargetActor = UGameplayStatics::GetActorOfClass(this, SpectatingViewingTarget);

			if (ViewingTargetActor != nullptr)
			{
				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();
					PC->SetViewTargetWithBlend(ViewingTargetActor, 0.5f, VTBlend_Cubic, 1.0F, false);
				}
			}

			else
			{
				UE_LOG(LogTemp, Log, TEXT("There is no viewing target actor in scene, pls create one!"));
			}
		}

		else
		{
			UE_LOG(LogTemp, Log, TEXT("Missing SpectatingViewingTarget Class, pls set this up in the Gamemode file."));
		}

		AFPSGameState* GS = GetGameState<AFPSGameState>();
		GS->MultiCastOnMissionComplete(PawnInstigator, bIsMissionScucess);
	}
}
