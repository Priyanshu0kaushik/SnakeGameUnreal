 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PersistantGameDataSubsystem.h"
#include "SnakeGameState.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API ASnakeGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	FGameData GameData;
	UFUNCTION(BlueprintCallable)
	void LoadWorld();
	UPersistantGameDataSubsystem* GameDataSubsystem = nullptr;
};
