// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakePawn.h"
#include "SnakeAIPlayerController.h"

void ASnakeAIPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakeAIPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SnakePawn = Cast<ASnakePawn>(InPawn);
}


void ASnakeAIPlayerController::Tick(float DeltaTime)
{
	if (!IsValid(SnakePawn)) return;
	SnakePawn->AddDirectionToQueue(ESnakeDirection::UP);	
}