// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMesh;
class ABullet;
class UBoxComponent;


UCLASS()
class TA2FEB_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;


	/** Classes that we set in blueprints */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<ABullet> Bullet_BP;


	/** Public Variables */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float ShotSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Lives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Score;

	/** Public Functions */
public:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
				bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HitByTarget();

	UFUNCTION()
	void StartSpeedBoost(float seconds);
	

	/** Private Variables */
private:

	float XInput;
	float YInput;

	float SpeedBoostTimer;
	float SpeedBoost;


private:
	/** Private Functions */

	void Forward(float input);
	void Right(float input);

	void Shoot();

	void Dodge();

	void StartShooting();
	void StopShooting();

	void Reload();


};
