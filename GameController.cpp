// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "Target.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"

AGameController::AGameController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialAmountToSpawn = 6;
	WaveAmount = 20;
	SpawnFrequency = 2.f;
	
	XMin = 2000;
	XMax = 2200;

	YMin = -400;
	YMax = 400;

	XKillTargetPosition = -500.f;
}

void AGameController::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(World, 0));
	for (int i{}; i < InitialAmountToSpawn; i++)
	{
		FVector location = FVector(FMath::RandRange(XMin, XMax), FMath::RandRange(YMin, YMax), 90);
		AActor* actor = World->SpawnActor<AActor>(Target_BP, location, FRotator::ZeroRotator);
		ATarget* target = Cast<ATarget>(actor);
		target->MovementSpeed += FMath::RandRange(0, 250);
		target->XKillPosition = XKillTargetPosition;
	}
}

void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Clock += DeltaTime;

	if (Clock > SpawnFrequency && WaveAmount > 0)
	{
		Clock = 0.f;
		WaveAmount--;
		FVector location = FVector(FMath::RandRange(XMin, XMax), FMath::RandRange(YMin, YMax), 90);
		AActor* actor = World->SpawnActor<AActor>(Target_BP, location, FRotator::ZeroRotator);
		ATarget* target = Cast<ATarget>(actor);
		target->MovementSpeed += FMath::RandRange(0, 250);
		target->XKillPosition = XKillTargetPosition;
	}
}
