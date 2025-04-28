// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeWorld.generated.h"

UCLASS()
class SNAKEGAME_API ASnakeWorld : public AActor
{
	GENERATED_BODY()
private:
	TArray<bool> LevelList;
public:	
	// Sets default values for this actor's properties
	ASnakeWorld();
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()	
	void OnWallOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
					   bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInstancedStaticMeshComponent* WallComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInstancedStaticMeshComponent* FloorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelID = "1";
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void LoadLevel(FString levelId);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
