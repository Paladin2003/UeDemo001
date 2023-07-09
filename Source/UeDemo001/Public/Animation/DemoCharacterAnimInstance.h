// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/DemoBaseAnimInstance.h"
#include "DemoCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoCharacterAnimInstance : public UDemoBaseAnimInstance
{
	GENERATED_BODY()

	UDemoCharacterAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
