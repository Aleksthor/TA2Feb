// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameController.generated.h"

class ATarget;
class AMyPlayer;

/**
 * 
 */
UCLASS()
class TA2FEB_API AGameController : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Public Variables */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int InitialAmountToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int WaveAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float SpawnFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float XMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float XMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float YMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float YMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float XKillTargetPosition;

	/** Classes that we set in blueprints */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<ATarget> Target_BP;


	/** Private Variables */

private:
	float Clock;
	AMyPlayer* Player;
	UWorld* World;

};
