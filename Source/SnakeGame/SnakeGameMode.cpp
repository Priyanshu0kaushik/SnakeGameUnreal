// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeAIPlayerController.h"
#include "PersistantGameDataSubsystem.h"
#include "SnakeGameMode.h"

#include "MainMenuWidget.h"

APlayerController* ASnakeGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	UPersistantGameDataSubsystem*  subSystem =  GetGameInstance()->GetSubsystem<UPersistantGameDataSubsystem>();

	if (subSystem->GetNoOfAIPlayerRequired()>AIPlayerCreated)
	{
		AIPlayerCreated++;
		UE_LOG(LogTemp, Log, TEXT("SpawnPlayerController spawned AI."));
		return GetWorld()->SpawnActor<ASnakeAIPlayerController>(ASnakeAIPlayerController::StaticClass());
	}
	
	UE_LOG(LogTemp, Log, TEXT("SpawnPlayerController spawned Simple "));
	
	return Super::SpawnPlayerController(InRemoteRole, Options);
}
