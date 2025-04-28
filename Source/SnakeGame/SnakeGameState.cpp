// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameState.h"

void ASnakeGameState::LoadWorld()
{
	if (GameDataSubsystem==nullptr)
	{
		if (GetGameInstance()->GetSubsystem<UPersistantGameDataSubsystem>() != nullptr)
		{
			GameDataSubsystem = GetGameInstance()->GetSubsystem<UPersistantGameDataSubsystem>();	
		}
		
	}
	UE_LOG(LogTemp, Log, TEXT("Loaded World snakegamestate"));
	GameData = GameDataSubsystem->GetPlayGameData();	
	
}
