// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include <FPSGame/Public/FPSPlayerController.h>

void AFPSGameState::MultiCastOnMissionComplete_Implementation(APawn* PawnInstigator, bool bIsMissionScucess)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionComplete(PawnInstigator, bIsMissionScucess);

			APawn* PlayerPawn = PC->GetPawn();
			if (PlayerPawn && PlayerPawn->IsLocallyControlled())
			{
				PlayerPawn->DisableInput(PC);
			}
		}

	}
}
