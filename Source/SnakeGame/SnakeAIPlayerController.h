// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core.h"
#include "GameFramework/PlayerController.h"
#include "SnakeAIPlayerController.generated.h"

/**
 * 
 */
class AStar;
class ASnakePawn;
class ASnakeWorld;
UCLASS()
class SNAKEGAME_API ASnakeAIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
	TObjectPtr<ASnakePawn> SnakePawn;
	TObjectPtr<ASnakeWorld> SnakeWorld;
	virtual void OnPossess(APawn* InPawn) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float findPathTime = 0.f;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	
	float timeCount = 0;
	AStar* AStarAgent;
	ESnakeDirection FindBestDirection();
};
