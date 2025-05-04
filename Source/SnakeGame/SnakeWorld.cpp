// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeWorld.h"
#include "SnakePawn.h"
#include "SnakeBody.h"
#include "Components/InstancedStaticMeshComponent.h"


// Sets default values
ASnakeWorld::ASnakeWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	WallComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Wall Component"));
	FloorComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Floor Component"));
	
	WallComponent->SetCollisionProfileName(TEXT("BlockAll"));
    
	FloorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WallComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeWorld::OnWallOverlapBegin);
	
	WallComponent->SetupAttachment(RootComponent);
	FloorComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASnakeWorld::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakeWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeWorld::LoadLevel(FString levelId){
	WallPositions.Empty();
	TArray<FString> lines;
	UE_LOG(LogTemp, Log, TEXT("loadlevel"));
	FString filePath = FPaths::ProjectDir() + TEXT("Levels/Level" + levelId + ".txt");
	
	if (FFileHelper::LoadFileToStringArray(lines, *filePath)) {
		if (lines.Num() != WORLD_HEIGHT) {
			UE_LOG(LogTemp, Log, TEXT("level height"));
			return;
		}
		int y = 0;
		
		for (FString line : lines) {
			if (line.Len() != WORLD_WIDTH) {
				UE_LOG(LogTemp, Log, TEXT("level width"));
				return;
			}
			for (int x = 0; x < line.Len(); x++) {
				bool IsWall = false;
				const int Index = y * WORLD_WIDTH + x;
				FVector location = FVector((lines.Num() - y) * TileSize, x * TileSize, 0.0f);
				FTransform offset = FTransform(FRotator::ZeroRotator, location );
				switch (line[x]) {
				case '#':
					WallComponent->AddInstance(offset);
					WallPositions.Add(location);
					IsWall = true;
					break;
				case '.':
					FloorComponent->AddInstance(offset);
					break;
				case 'O':
					break;
				default:
					break;
				}
				 // LevelList[index] = IsWall;
			}
			y++;

		}
		UE_LOG(LogTemp, Log, TEXT("No. of Walls: %d"), WallPositions.Num());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("file not found"));
		printf("no file found.");
	}
}


void ASnakeWorld::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Log, TEXT("callledd"));
	LevelList.Empty();
	WallComponent->ClearInstances();
	FloorComponent->ClearInstances();
	LoadLevel(LevelID);
}

void ASnakeWorld::OnWallOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASnakePawn* snakePawn = Cast<ASnakePawn>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Wall Collision with Snake"));
		// game over
	}
}

bool ASnakeWorld::IsWall(int inX, int inY)
{
	if(inX >= WORLD_WIDTH || inY >= WORLD_HEIGHT || inX < 0 || inY < 0) return false;

	return LevelList[inY * WORLD_WIDTH + inX];
}
