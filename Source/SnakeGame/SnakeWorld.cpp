// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeWorld.h"
#include "Core.h"
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
				FTransform offset = FTransform(FRotator::ZeroRotator, FVector((lines.Num() - y) * 100, x * 100, 0.0f));
				switch (line[x]) {
				case '#':
					WallComponent->AddInstance(offset);
					break;
				case '.':
					FloorComponent->AddInstance(offset);
					break;
				case 'O':
					break;
				}
			}

			y++;

		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("file not found"));
		printf("no file found.");
	}
}


void ASnakeWorld::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Log, TEXT("callledd"));
	WallComponent->ClearInstances();
	FloorComponent->ClearInstances();
	LoadLevel(LevelID);


}
