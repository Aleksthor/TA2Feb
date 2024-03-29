// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/BoxComponent.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(10,50,50));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnOverlap);


	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	StaticMesh->SetupAttachment(Collider);
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));

	MovementSpeed = 250.f;
	RotationSpeed = 1.f;
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	RotationSpeed = FMath::RandRange(0.5f,1.5f);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();

	NewLocation += FVector(-1,0,0) * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	SetActorRotation(GetActorRotation() + FRotator(0, RotationSpeed, 0));


	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}
}

void ATarget::DestroyTarget()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

void ATarget::GainScore()
{
	AMyPlayer* Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->Score += 100;
}

void ATarget::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent->IsA<UCapsuleComponent>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Something hit the target"));

	}
	if (OtherActor->IsA<AMyPlayer>())
	{
		Cast<AMyPlayer>(OtherActor)->HitByTarget();
		DestroyTarget();
	}
}

