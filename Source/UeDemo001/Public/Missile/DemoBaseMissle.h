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
	// Sets default values for this actor's properties
	ADemoBaseMissle();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UProjectileMovementComponent* Movement;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* Partical;
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
