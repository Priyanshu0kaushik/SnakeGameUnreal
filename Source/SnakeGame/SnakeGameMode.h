#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Apple.h"
#include "SnakeGameMode.generated.h"

class ASnakePawn;
class ASnakeWorld;
UCLASS()
class SNAKEGAME_API ASnakeGameMode : public AGameMode
{
	GENERATED_BODY()
	
	
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
public:
	void OnAppleEaten();
	FVector GetAppleLocation();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AApple> SpawnedAppleClass;
	TArray<FVector> GetOccupiedLocations();

private:
	AApple* CurrentApple;
	ASnakeWorld* snakeWorld;
	int AIPlayerCreated = 0;
	int CurrentAppleCount = 1;
	UFUNCTION(BlueprintCallable)
	void SpawnApple();
	UFUNCTION(BlueprintCallable)
	void Init();

	FVector GetRandomLocation();
};
