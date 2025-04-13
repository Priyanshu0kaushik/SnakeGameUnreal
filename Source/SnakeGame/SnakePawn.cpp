// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = sceneComponent;
    
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    FVector Position = GetActorLocation();
    // Update speed
    VelocityZ -= 10.0f * DeltaTime;
    // Update movement
    Position.Z += VelocityZ;
    
    // Check floor collisions
    if(Position.Z <= 0.0f){
        Position.Z = 0.0f;
        VelocityZ = -VelocityZ * 0.5f;
        if(FMath::Abs(VelocityZ) < 0.2f){
            VelocityZ = 0.0f;
            Position.Z = 0.0f;
            bGrounded = true;
        }
    }
    else{
        bGrounded = false;
    }
    
    Move(DeltaTime);
    
    Position += Direction;
    SetActorLocation(Position);

}

void ASnakePawn::AddDirectionToQueue(ESnakeDirection direction){
    directionQueue.Emplace(direction);
}

void ASnakePawn::Move(float deltaTime){
    if(directionQueue.IsEmpty()) return;
    
    ESnakeDirection currentDirection = directionQueue[0];
    directionQueue.RemoveAt(0);
    
    switch(currentDirection){
        case ESnakeDirection::UP:
            if(previousDirection == ESnakeDirection::DOWN) return;
            Direction = FVector::ZeroVector;
            Direction.X = Speed * deltaTime;
            previousDirection = currentDirection;
            CollisionComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
            break;
        case ESnakeDirection::RIGHT:
            if(previousDirection == ESnakeDirection::LEFT) return;
            Direction = FVector::ZeroVector;
            Direction.Y += Speed * deltaTime;
            previousDirection = currentDirection;
            CollisionComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
            break;
        case ESnakeDirection::DOWN:
            if(previousDirection == ESnakeDirection::UP) return;
            Direction = FVector::ZeroVector;
            Direction.X -= Speed * deltaTime;
            previousDirection = currentDirection;
            CollisionComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
            break;
        case ESnakeDirection::LEFT:
            if(previousDirection == ESnakeDirection::RIGHT) return;
            Direction = FVector::ZeroVector;
            Direction.Y -= Speed * deltaTime;
            previousDirection = currentDirection;
            CollisionComponent->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
            break;
        default:
            return;
            break;
    }
}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASnakePawn::Jump(){
//    VelocityZ = 10.f;
    if(bGrounded){
        VelocityZ = 10.f;
    }
    
}

