// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SnakeBody.generated.h"

UCLASS()
class SNAKEGAME_API ASnakeBody : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBody();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USceneComponent* sceneComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent* CollisionComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TSubclassOf<ASnakeBody> SnakeBodyPart; 
	
	FVector<ASnakeBody*> Body;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
