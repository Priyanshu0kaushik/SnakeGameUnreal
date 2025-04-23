#include "SnakeBody.h"


// Sets default values
ASnakeBody::ASnakeBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = sceneComponent;
    
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASnakeBody::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NextPosition != FVector::ZeroVector)
	{
		FVector Position = GetActorLocation();

		FVector Forward = (NextPosition - Position).GetSafeNormal();

		Position += Forward * DeltaTime * 500.0f;

		SetActorLocation(Position);

	}

}

void ASnakeBody::SetNextPosition(const FVector& InPosition)
{
	if (IsValid(ChildBodyPart))
	{
		ChildBodyPart->SetNextPosition(NextPosition);
	}

	NextPosition = InPosition;
}

void ASnakeBody::AddChildBodyPart(ASnakeBody* InChildBodyPart)
{
	if (IsValid(ChildBodyPart))
	{
		ChildBodyPart->AddChildBodyPart(InChildBodyPart);
	}
	else
	{
		ChildBodyPart = InChildBodyPart;

		ChildBodyPart->SetActorLocation(GetActorLocation());
	}
}