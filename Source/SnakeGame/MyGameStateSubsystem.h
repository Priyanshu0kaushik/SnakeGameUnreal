// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyGameStateSubsystem.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	None,
	Menu,
	Play,
	Pause,
	Outro
};
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameStateChanged, EGameState, OldGameState, EGameState, NewGameState);

UCLASS()
class SNAKEGAME_API UMyGameStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY()
	EGameState CurrentGameState = EGameState::Menu;

	EGameState PreviousGameState = EGameState::None;
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChanged OnStateChanged;
	
	UFUNCTION(BlueprintCallable)
	inline EGameState GetGameState() const {return CurrentGameState;}

	UFUNCTION(BlueprintCallable)
	void ChangeGameState(EGameState NewGameState);

};
