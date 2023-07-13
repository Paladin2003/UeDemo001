// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DemoBaseMissle.generated.h"

UCLASS()
class UEDEMO001_API ADemoBaseMissle : public AActor
{
	GENERATED_BODY()

public:

	ADemoBaseMissle();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UProjectileMovementComponent* Movement;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damage")
	int32 Damage = 3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* Partical;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystem* BoomParticle;

	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bOverlapped = false;
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DestroyDelayTime;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;
};
