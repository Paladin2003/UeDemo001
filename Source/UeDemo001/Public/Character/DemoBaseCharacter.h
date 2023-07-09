// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoBaseCharacter.generated.h"

UCLASS()
class UEDEMO001_API ADemoBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoBaseCharacter();

protected:
	/**
	 * @brief 是否奔跑
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Movement")
	bool bIsRunning;
	/**
	 * @brief 移动速率
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Movement")
	float MovementRate;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Init")
	//骨骼网格体的初始旋转
	FRotator DefaultRotateForSkm = FRotator(0,-90,0);

	void CharacterRotate(FVector Vector);
};
