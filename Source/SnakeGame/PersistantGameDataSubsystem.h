// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PersistantGameDataSubsystem.generated.h"

enum class EPlayersNum : uint8;
enum class EGameMode : uint8;

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_BODY()
	
	EPlayersNum NumOfPlayers;
	EGameMode GameMode;
	
};

/**
 * 
 */
UCLASS()
class SNAKEGAME_API UPersistantGameDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	FGameData PlayGameData;
public:
	UFUNCTION(BlueprintCallable)
	void SetPlayGameData(EPlayersNum NumOfPlayers, EGameMode GameMode);
	UFUNCTION(BlueprintCallable)
	FGameData GetPlayGameData() const{ return PlayGameData; } 
	UFUNCTION(BlueprintCallable)
	EPlayersNum GetNoOfPlayer() {return PlayGameData.NumOfPlayers; }
	UFUNCTION(BlueprintCallable)
	EGameMode GetGameMode() {return PlayGameData.GameMode; }
	
};
