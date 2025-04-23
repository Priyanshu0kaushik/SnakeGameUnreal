// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
UCLASS()
class SNAKEGAME_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	EMenuState CurrentMenuState = EMenuState::BASE;
	UPROPERTY(BlueprintReadWrite)
	int CurrentGameMode = static_cast<int>(EGameMode::None);
	UPROPERTY(BlueprintReadWrite)
	int CurrentNumPlayers = static_cast<int>(EPlayersNum::One);
	
};
