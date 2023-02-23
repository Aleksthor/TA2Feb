// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Bullet.h"



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
	SpringArm->bUsePawnControlRotation = true;

	// Stand still when camera moves
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetRootComponent());
	Collider->InitBoxExtent(FVector(50, 50, 50));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnOverlap);
	Collider->SetRelativeLocation(FVector(0, 0, 50));


	Speed = 100.f;
	Ammo = 10;
	MaxAmmo = Ammo;

	SpeedBoostTimer = 0;
	SpeedBoost = 2;
	


	ShotSpeed = 1.f;
	Lives = 5;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	Score = 0;
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float MovementSpeed = Speed;

	if (SpeedBoostTimer > 0.f)
	{
		SpeedBoostTimer -= DeltaTime;
		MovementSpeed *= SpeedBoost;
	}


	// Ensures no crashing checking if its not a nullptr
	if ((Controller != nullptr) && (XInput != 0.f))
	{
		// Find out what way is forward
		// Getting the Vector of the Controller. This is our SpringArm
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // Canceling out X and Z Rotation.

		// Here we are basically getting the local X vector with a unit of 1
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		SetActorLocation(GetActorLocation() + Direction * XInput * MovementSpeed * DeltaTime);

		SetActorRotation(YawRotation);
	}

	// Ensures no crashing checking if its not a nullptr
	if ((Controller != nullptr) && (YInput != 0.f))
	{
		// Find out what way is forward
		// Getting the Vector of the Controller. This is our SpringArm
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // Canceling out X and Z Rotation.

		// Here we are basically getting the local Y vector with a unit of 1
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		SetActorLocation(GetActorLocation() + Direction * YInput * MovementSpeed * DeltaTime);
		SetActorRotation(YawRotation);
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("Forward", this, &AMyPlayer::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMyPlayer::Right);
	PlayerInputComponent->BindAxis("MouseX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayer::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyPlayer::Reload);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AMyPlayer::Dodge);

	//PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayer::StartShooting);
	//PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMyPlayer::StopShooting);
}

void AMyPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // Canceling out X and Z Rotation.

		// Here we are basically getting the local X vector with a unit of 1
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		GetWorld()->SpawnActor<AActor>(Bullet_BP,									// What to spawn
			GetActorLocation() + (Direction * 30),		// Location
			YawRotation);								// Rotation


		Ammo--;
	}
}

void AMyPlayer::Dodge()
{

	FVector NewLocation = GetActorLocation() + GetActorRightVector() * YInput * 350.f;
	SetActorLocation(NewLocation);

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
	//UGameplayStatics::PlaySound2D(World, Sound)
}
void AMyPlayer::HitByTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	Lives--;
	if (Lives <= 0)
	{
		// TODO : Game Over
	}
}

void AMyPlayer::StartSpeedBoost(float seconds)
{
	SpeedBoostTimer += seconds;
}
