// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateSubsystem.h"

void UMyGameStateSubsystem::ChangeGameState(EGameState NewGameState)
{
	if (PreviousGameState == NewGameState) return;
	PreviousGameState = CurrentGameState;
	CurrentGameState = NewGameState;
	OnStateChanged.Broadcast(PreviousGameState, CurrentGameState);
}
