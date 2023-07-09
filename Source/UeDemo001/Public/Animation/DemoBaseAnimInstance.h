// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimInstance.h"
#include "DemoBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDemoBaseAnimInstance();
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float Velocity;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attack")
	bool bAttacking;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
