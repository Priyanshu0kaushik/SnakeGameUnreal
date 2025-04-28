#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SnakeGameMode.generated.h"

UCLASS()
class SNAKEGAME_API ASnakeGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
	
	private:
	int AIPlayerCreated = 0;
};
