// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyGameStateSubsystem.h"
#include "MainMenuWidget.generated.h"

UENUM(BlueprintType)
enum class EPlayersNum : uint8
{
	One,
	Two,
	End
};

UENUM(BlueprintType)
enum class EGameMode : uint8
{
	None,
	CLASSIC,
	COOP,
	BATTLE,
	End
};

UENUM(BlueprintType)
enum class EMenuState : uint8
{
	None,
	BASE,
	NEWGAMELEVEL,
	End
};

/**
 * 
 */

class UPersistantGameDataSubsystem;

UCLASS()
class SNAKEGAME_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	EMenuState CurrentMenuState = EMenuState::BASE;
	UPROPERTY(BlueprintReadWrite)
	int CurrentGameMode = static_cast<int>(EGameMode::CLASSIC);
	UPROPERTY(BlueprintReadWrite)
	int CurrentNumPlayers = static_cast<int>(EPlayersNum::One);
	
	UFUNCTION(BlueprintCallable)
	EGameMode IntToGameMode(int a){
		return static_cast<EGameMode>(a);
	}
	UFUNCTION(BlueprintCallable)
	EPlayersNum IntToPlayersNum(int a){
		return static_cast<EPlayersNum>(a);
	}


	UFUNCTION(BlueprintCallable)
	void Init();
	
	UFUNCTION(BlueprintCallable)
	void OnPressSelected(int index);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeMenuState(EMenuState state);
private:
	UMyGameStateSubsystem* myGameStateSubsystem = nullptr;
	UPersistantGameDataSubsystem* myPersistantGameDataSubsystem = nullptr;
	void SaveWorld();
	
 };
