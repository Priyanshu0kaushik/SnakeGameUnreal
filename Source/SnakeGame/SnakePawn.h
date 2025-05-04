// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "Core.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeBody.h"
#include "SnakePawn.generated.h"

class ASnakeGameMode;
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
    ASnakeGameMode* GameMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ESnakeDirection> directionQueue;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    void Move(float deltaTime);
    void GravityUpdate(FVector& Position, float DeltaTime);
    void AteApple();
	void Grow();
	FVector DirectionToVector(ESnakeDirection Direction);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASnakeBody> SnakeBodyPart;
	

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bGrounded = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float VelocityZ = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Speed = 100.f;
    float movedTileDistance = 0.0f;
    FVector Direction{0.0f, 0.0f, 0.0f};
    ESnakeDirection previousDirection =  ESnakeDirection::UP;
	
	UPROPERTY()
	ASnakeBody* ChildBodyPart = nullptr;
	
public:
	DECLARE_MULTICAST_DELEGATE(FOnAppleEaten);
	FOnAppleEaten AppleEatenDelegate;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
					   bool bFromSweep, const FHitResult& SweepResult);
	
    UFUNCTION(BlueprintCallable)
    void Jump();
    
    UFUNCTION(BlueprintCallable)
    void AddDirectionToQueue(ESnakeDirection Direction);
	

};
