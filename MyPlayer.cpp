// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetRelativeLocation(FVector(0,0,0));
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Speed = 100.f;
	Ammo = 10;
	MaxAmmo = Ammo;
	


	ShotSpeed = 1.f;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + FVector(XInput, YInput, 0.f) * Speed * DeltaTime;
	GetRootComponent()->SetWorldLocation(NewLocation);
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMyPlayer::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMyPlayer::Right);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayer::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyPlayer::Reload);

	//PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayer::StartShooting);
	//PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyPlayer::StopShooting);
}

void AMyPlayer::Forward(float input)
{
	XInput = input;
}
void AMyPlayer::Right(float input)
{
	YInput = input;
}

void AMyPlayer::Shoot()
{

	if (Ammo > 0)
	{
		GetWorld()->SpawnActor<AActor>(Bullet_BP,			// What to spawn
									   GetActorLocation() + FVector(30,0,0), 	// Location 
									   GetActorRotation());	// Bullet will spawn with same rotation as we have
		Ammo--;
	}
}

void AMyPlayer::StartShooting()
{

}
void AMyPlayer::StopShooting()
{

}

void AMyPlayer::Reload()
{
	Ammo = MaxAmmo;
}