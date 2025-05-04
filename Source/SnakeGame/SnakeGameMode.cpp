// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"
#include "Core.h"
#include "SnakeWorld.h"
#include "SnakePawn.h"
#include "SnakeBody.h"
#include "SnakeAIPlayerController.h"
#include "PersistantGameDataSubsystem.h"
#include "Kismet/GameplayStatics.h"



APlayerController* ASnakeGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	UPersistantGameDataSubsystem*  subSystem =  GetGameInstance()->GetSubsystem<UPersistantGameDataSubsystem>();

	
	int ControllersCount = UGameplayStatics::GetNumPlayerControllers(GetWorld());

	if (subSystem->GetNoOfAIPlayerRequired()>AIPlayerCreated && ControllersCount>0)
	{
		AIPlayerCreated++;
		UE_LOG(LogTemp, Log, TEXT("SpawnPlayerController spawned AI."));
		return GetWorld()->SpawnActor<ASnakeAIPlayerController>(ASnakeAIPlayerController::StaticClass());
	}
	
	UE_LOG(LogTemp, Log, TEXT("SpawnPlayerController spawned Simple "));
	
	return Super::SpawnPlayerController(InRemoteRole, Options);
}

// void ASnakeGameMode::BeginPlay()
// {
// 	
// 	SpawnApple();
//
// }

void ASnakeGameMode::Init()
{
	snakeWorld = Cast<ASnakeWorld>(UGameplayStatics::GetActorOfClass(GetWorld(), ASnakeWorld::StaticClass()));
    if (IsValid(snakeWorld))
    {
    	UE_LOG(LogTemp, Log, TEXT("Snake World Is Valid"));	
    }
}



void ASnakeGameMode::SpawnApple()
{
	TArray<FVector> occupiedLocs = GetOccupiedLocations();
	UE_LOG(LogTemp, Log, TEXT("First loc z:%d"), (int)occupiedLocs[0].X);

	CurrentApple = GetWorld()->SpawnActor<AApple>(SpawnedAppleClass, GetRandomLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
	if (CurrentApple)
	{
		UE_LOG(LogTemp, Log, TEXT("Apple spawned at %s"), *CurrentApple->GetActorLocation().ToString());
	}
}

TArray<FVector> ASnakeGameMode::GetOccupiedLocations()
{
	TArray<FVector> OccupiedLocations;
	TArray<AActor*> SnakeBodyActors;
	TArray<AActor*> SnakePawnActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ASnakeBody::StaticClass(), SnakeBodyActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASnakePawn::StaticClass(), SnakePawnActors);
	if(snakeWorld)
	{
		OccupiedLocations.Append(snakeWorld->WallPositions);	
	}
	for (AActor* Actor : SnakeBodyActors)
	{
		OccupiedLocations.Add(Actor->GetActorLocation());
	}
	for(AActor* Actor : SnakePawnActors)
	{
		OccupiedLocations.Add(Actor->GetActorLocation());
	}
	return OccupiedLocations;
}

FVector ASnakeGameMode::GetRandomLocation()
{
	int x,y,z;
	z = 0;
	x = rand()%(int)WORLD_HEIGHT;
	y = rand()%(int)WORLD_WIDTH;
	x *=TileSize;
	y *=TileSize;
	for(FVector pos : GetOccupiedLocations())
	{
		if(pos.X == x && pos.Y == y) return GetRandomLocation();
	}
	UE_LOG(LogTemp, Log, TEXT("Random Location %d %d"), x, y);
	return FVector(x,y,15);
}

void ASnakeGameMode::OnAppleEaten()
{
	CurrentAppleCount--;
	SpawnApple();
}

FVector ASnakeGameMode::GetAppleLocation()
{
	return CurrentApple->GetActorLocation();
	
}