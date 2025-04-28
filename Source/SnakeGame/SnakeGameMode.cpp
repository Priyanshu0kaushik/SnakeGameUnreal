// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeAIPlayerController.h"
#include "PersistantGameDataSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"



APlayerController* ASnakeGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	UPersistantGameDataSubsystem*  subSystem =  GetGameInstance()->GetSubsystem<UPersistantGameDataSubsystem>();

	
	int ControllersCount = UGameplayStatics::GetNumPlayerControllers(GetWorld());

	if (subSystem->GetNoOfAIPlayerRequired()>AIPlayerCreated && ControllersCount>0)
	{
		AIPlayerCreated++;
		UE_LOG(LogTemp, Log, TEXT("SpawnPlayerController spawned AI."));
		return GetWorld()->SpawnActor<ASnakeAIPlayerController>(ASnakeAIPlayerController::StaticClass());
	}
	
	UE_LOG(LogTemp, Log, TEXT("SpawnPlayerController spawned Simple "));
	
	return Super::SpawnPlayerController(InRemoteRole, Options);
}
