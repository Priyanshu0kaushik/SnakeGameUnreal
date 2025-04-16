// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_SnakeBody.h"


// Sets default values
ABP_SnakeBody::ABP_SnakeBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = sceneComponent;
    
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABP_SnakeBody::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_SnakeBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

