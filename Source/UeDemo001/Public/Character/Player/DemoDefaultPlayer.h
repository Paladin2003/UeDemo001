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

	/**
	 * @brief 转向动作
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> LookUpInputAction;

	/**
	 * @brief 奔跑动作
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> RunningInputAction;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	/**
	 * @brief 开启增强输入
	 */
	void InitEnhancedInput();

	virtual void MovementForEnhancedInput(const FInputActionValue& InputActionValue);

	virtual void LookUpForEnhancedInput(const FInputActionValue& InputActionValue);

	virtual void RunningForEnhancedInput(const FInputActionValue& InputActionValue);

	void BindInputAction(TObjectPtr<UInputAction> InputAction,ETriggerEvent TriggerEvent,FName FunctionName);
};
