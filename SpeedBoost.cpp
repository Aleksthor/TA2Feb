// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "Components/BoxComponent.h"
#include "MyPlayer.h"

// Sets default values
ASpeedBoost::ASpeedBoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetRootComponent());
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpeedBoost::OnOverlap);

}

// Called when the game starts or when spawned
void ASpeedBoost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpeedBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpeedBoost::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AMyPlayer>())
	{
		Cast<AMyPlayer>(OtherActor)->StartSpeedBoost(4);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		this->Destroy();
	}
}

