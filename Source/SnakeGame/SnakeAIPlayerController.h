// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakeAIPlayerController.generated.h"

/**
 * 
 */

class ASnakePawn;

UCLASS()
class SNAKEGAME_API ASnakeAIPlayerController : public APlayerController
{
	GENERATED_BODY()
	TObjectPtr<ASnakePawn> SnakePawn;
	virtual void OnPossess(APawn* InPawn) override;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
