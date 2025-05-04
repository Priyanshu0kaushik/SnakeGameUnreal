// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeAIPlayerController.h"
#include "AStar.h"
#include "SnakeGameMode.h"
#include "SnakePawn.h"
#include "SnakeWorld.h"
#include "Kismet/GameplayStatics.h"

void ASnakeAIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> SnakeWorlds;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASnakeWorld::StaticClass(), SnakeWorlds);
	if (SnakeWorlds.Num() == 0) return;

	SnakeWorld = Cast<ASnakeWorld>(SnakeWorlds[0]);
	AStarAgent = new AStar();
	
}

void ASnakeAIPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SnakePawn = Cast<ASnakePawn>(InPawn);
}


void ASnakeAIPlayerController::Tick(float DeltaTime)
{
	if (!IsValid(SnakePawn) || !IsValid(SnakeWorld)) return;
	timeCount+=DeltaTime;
	if(timeCount>findPathTime)
	{
		ESnakeDirection direction = FindBestDirection();
		UE_LOG(LogTemp, Display, TEXT("Direction %s"), *UEnum::GetValueAsString(direction));
		SnakePawn->directionQueue.Empty();
		SnakePawn->AddDirectionToQueue(direction);
		timeCount=0;
	}
}




ESnakeDirection ASnakeAIPlayerController::FindBestDirection()
{
	FVector Location = SnakePawn->GetActorLocation();
	int X = (int)(Location.X / TileSize);
	int Y = (int)(Location.Y / TileSize);
	FVector TargetLocation = SnakePawn->GameMode->GetAppleLocation();
	TArray<FVector> OccupiedTiles = SnakePawn->GameMode->GetOccupiedLocations();
	if (!AStarAgent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AStarAgent Null"));
		return ESnakeDirection::NONE;
	}
	TArray<FVector> Path = AStarAgent->FindPath(Location, TargetLocation, OccupiedTiles);
	UE_LOG(LogTemp, Log, TEXT("Path Length: %d"), Path.Num());
	
	if (Path.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No path found"));
		return ESnakeDirection::UP;
	}
	UE_LOG(LogTemp, Log, TEXT("First Loc %d %d Current Location %d %d"), (int)Path[1].X, (int)Path[1].Y, X, Y);
	if (Path[1].X == X)
	{
		if (Path[1].Y > Y)
			return ESnakeDirection::RIGHT;
	
		return ESnakeDirection::LEFT;
	}

	if (Path[1].X > X)
		return ESnakeDirection::UP;

	return ESnakeDirection::DOWN;
}
