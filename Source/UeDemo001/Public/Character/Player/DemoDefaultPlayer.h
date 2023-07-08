// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Character/DemoBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DemoDefaultPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoDefaultPlayer : public ADemoBaseCharacter
{
	GENERATED_BODY()

	ADemoDefaultPlayer();

protected:
	/**
	 * @brief 移动速率
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Movement")
	float MovementRate;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USpringArmComponent* CameraArm;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCameraComponent* Camera;

	/**
	 * @brief 移动场景映射
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputMappingContext> MovementInputMappingContext;

	/**
	 * @brief 移动动作
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> MovementInputAction;

	virtual void BeginPlay() override;

	virtual void Move();
	
private:
	/**
	 * @brief 开启增强输入
	 */
	void InitEnhancedInput();

	virtual void MovementForEnhancedInput(const FInputActionValue& InputActionValue);
};
