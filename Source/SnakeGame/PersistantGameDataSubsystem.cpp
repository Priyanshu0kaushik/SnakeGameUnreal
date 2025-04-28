// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistantGameDataSubsystem.h"

#include "MainMenuWidget.h"

void UPersistantGameDataSubsystem::SetPlayGameData(EPlayersNum NumPlayers, EGameMode PlayGameMode)
{
	PlayGameData.NumOfPlayers = NumPlayers;
	PlayGameData.GameMode = PlayGameMode;
}

int UPersistantGameDataSubsystem::GetNoOfPlayer()
{
	return static_cast<int>(PlayGameData.NumOfPlayers)+1;
}

int UPersistantGameDataSubsystem::GetNoOfAIPlayerRequired()
{
	if (GetGameMode() == EGameMode::CLASSIC || GetNoOfPlayer()==2) return 0;
	else return 1;
}




