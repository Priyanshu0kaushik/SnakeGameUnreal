// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameStateSubsystem.h"
#include "SnakeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintCallable, Category = "Game State")
		UMyGameStateSubsystem* GetMyGameStateSubsystem() const
		{
			return GetSubsystem<UMyGameStateSubsystem>();
		}
	

};
