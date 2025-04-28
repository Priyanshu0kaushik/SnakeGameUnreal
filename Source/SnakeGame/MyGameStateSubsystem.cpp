// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UMyGameStateSubsystem::ChangeGameState(EGameState NewGameState)
{
	if (PreviousGameState == NewGameState) return;
	PreviousGameState = CurrentGameState;
	CurrentGameState = NewGameState;
	// OnStateChanged.Broadcast(PreviousGameState, CurrentGameState);

	switch (NewGameState)
	{
	case EGameState::Menu:
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
		break;
	case EGameState::Play:
		UGameplayStatics::OpenLevel(GetWorld(), "NewMap");
		break;
	default:
		break;
	}
	
}
