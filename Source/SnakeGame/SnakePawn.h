// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "Core.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

UCLASS()
class SNAKEGAME_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawn();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USceneComponent* sceneComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent* CollisionComponent;
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float VelocityZ = 0.0f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bGrounded = false;
    
    FVector Direction{0.0f, 0.0f, 0.0f};
    
    float Speed = 100.f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<ESnakeDirection> directionQueue;
    
    ESnakeDirection previousDirection =  ESnakeDirection::UP;
    
    void Move(float deltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UFUNCTION(BlueprintCallable)
    void Jump();
    
    UFUNCTION(BlueprintCallable)
    void AddDirectionToQueue(ESnakeDirection Direction);
};
