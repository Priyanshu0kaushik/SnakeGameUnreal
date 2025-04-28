// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistantGameDataSubsystem.h"

void UPersistantGameDataSubsystem::SetPlayGameData(EPlayersNum NumPlayers, EGameMode PlayGameMode)
{
	PlayGameData.NumOfPlayers = NumPlayers;
	PlayGameData.GameMode = PlayGameMode;
}
