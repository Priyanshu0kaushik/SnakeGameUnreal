// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "PersistantGameDataSubsystem.h"

void UMainMenuWidget::Init()
{
	if (GetGameInstance()->GetSubsystem<UMyGameStateSubsystem>() != nullptr)
	{
		myGameStateSubsystem = GetGameInstance()->GetSubsystem<UMyGameStateSubsystem>();
	}
	
	if (GetGameInstance()->GetSubsystem<UPersistantGameDataSubsystem>() != nullptr)
	{
		myPersistantGameDataSubsystem = GetGameInstance()->GetSubsystem<UPersistantGameDataSubsystem>();
	}
			
}

void UMainMenuWidget::OnPressSelected(int index)
{
	switch (CurrentMenuState)
	{
	case EMenuState::BASE:
		switch (index)
		{
		// New Game button
		case 0:
			UE_LOG(LogTemp, Log, TEXT("Called"));
			ChangeMenuState(EMenuState::NEWGAMELEVEL);
			break;
		// Option button
		case 1:
			break;
		// Quit button
	    case 2:
			//Quit
			break;
		default:
			break;
		}
		break;

	case EMenuState::NEWGAMELEVEL:
		switch (index)
		{
		//Start
		case 0:
			if (myGameStateSubsystem!= nullptr)
			{
				SaveWorld();
				myGameStateSubsystem->ChangeGameState(EGameState::Play);
			}
			else UE_LOG(LogTemp, Log, TEXT("myGameState null"));
			// To Play
			break;
		// Back
		case 3:
			ChangeMenuState(EMenuState::BASE);
			break;
		default:
			break;
		}
		break;
	default:
		break;
		
	}
}

void UMainMenuWidget::SaveWorld()
{
	if (myPersistantGameDataSubsystem!= nullptr)
	{
		myPersistantGameDataSubsystem->SetPlayGameData(static_cast<EPlayersNum>(CurrentNumPlayers), static_cast<EGameMode>(CurrentGameMode));
		UE_LOG(LogTemp, Log, TEXT("Saved World"));
	}
}

