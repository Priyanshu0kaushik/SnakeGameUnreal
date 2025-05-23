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

	void AddChildBodyPart(ASnakeBody* InChildBodyPart);
	
	ASnakeBody* GetChildBodyPart() const{return ChildBodyPart;}
protected:
	UPROPERTY()
	ASnakeBody* ChildBodyPart = nullptr;

	UPROPERTY()
	FVector NextPosition = FVector::ZeroVector;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void SetNextPosition(const FVector& InPosition);
	
	
};
