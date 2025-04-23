// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Apple.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = sceneComponent;
    
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetupAttachment(RootComponent);
    
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakePawn::OnOverlapBegin);
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
    
    movedTileDistance += Speed * DeltaTime;
    FVector Position = GetActorLocation();
    
    if(movedTileDistance > TileSize){
        movedTileDistance = 0.f;
        Move(DeltaTime);
        if (IsValid(ChildBodyPart))
        {
            ChildBodyPart->SetNextPosition(GetActorLocation());
        }
    }
    
    GravityUpdate(Position, DeltaTime);
    Position += Direction;
    SetActorLocation(Position);

}

void ASnakePawn::GravityUpdate(FVector& Position, float DeltaTime){
    
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
}


void ASnakePawn::AddDirectionToQueue(ESnakeDirection direction){
    directionQueue.Emplace(direction);
}

void ASnakePawn::Move(float deltaTime){
    if(directionQueue.IsEmpty()) return;
    
    ESnakeDirection currentDirection = directionQueue[0];
    directionQueue.RemoveAt(0);

    if (currentDirection == ESnakeDirection::UP && previousDirection == ESnakeDirection::DOWN) return;
    if (currentDirection == ESnakeDirection::DOWN && previousDirection == ESnakeDirection::UP) return;
    if (currentDirection == ESnakeDirection::RIGHT && previousDirection == ESnakeDirection::LEFT) return;
    if (currentDirection == ESnakeDirection::LEFT && previousDirection == ESnakeDirection::RIGHT) return;
    
    FVector direction = DirectionToVector(currentDirection);

    Direction = direction * Speed * deltaTime;
    previousDirection = currentDirection;
    
    FRotator NewRotation = Direction.Rotation();
    CollisionComponent->SetWorldRotation(NewRotation);
}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASnakePawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AApple* apple = Cast<AApple>(OtherActor))
    {
        UE_LOG(LogTemp, Log, TEXT("Collision with Apple"));
        AteApple();
    }
}

void ASnakePawn::Jump(){
//    VelocityZ = 10.f;
    if(bGrounded){
        VelocityZ = 5.f;
    }   
}

void ASnakePawn::AteApple(){
    Grow();
}

void ASnakePawn::Grow()
{
    ASnakeBody* BodyPart = GetWorld()->SpawnActor<ASnakeBody>(SnakeBodyPart, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());

    if (IsValid(ChildBodyPart))
    {
        ChildBodyPart->AddChildBodyPart(BodyPart);
    }
    else
    {
        ChildBodyPart = BodyPart;
    }
}

FVector ASnakePawn::DirectionToVector(ESnakeDirection Direction)
{
    switch (Direction)
    {
        case ESnakeDirection::UP:
            return FVector::ForwardVector;
        case ESnakeDirection::RIGHT:
            return FVector::RightVector;
        case ESnakeDirection::DOWN:
            return FVector::BackwardVector;
        case ESnakeDirection::LEFT:
            return FVector::LeftVector;
        case ESnakeDirection::NONE:
            return FVector::ZeroVector;
    }
    return FVector::ZeroVector;
}



