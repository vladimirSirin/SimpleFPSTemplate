// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"

void AFPSGameState::MultiCastOnMissionComplete_Implementation(APawn* PawnInstigator, bool bIsMissionScucess)
{
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		APawn* PlayerPawn = It->Get();

		if (PlayerPawn->IsLocallyControlled())
		{
			PlayerPawn->DisableInput(nullptr);

		}
	}
}
