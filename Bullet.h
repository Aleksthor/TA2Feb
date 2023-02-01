// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TA2FEB_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Collider{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	/** Public Variables*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float LifeSpan;

	/** Public Functions */

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
				bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyBullet();


	/** Private Variables */
private:
	float TimeLived;
};
