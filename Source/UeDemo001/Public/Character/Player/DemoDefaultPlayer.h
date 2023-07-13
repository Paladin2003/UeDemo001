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

public:

	virtual void AttackFireBall() override;
	
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
	 * @brief 移动输入
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> MovementInputAction;

	/**
	 * @brief 转向输入
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> LookUpInputAction;

	/**
	 * @brief 奔跑输入
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> RunningInputAction;

	/**
	 * @brief 攻击输入
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> AttackInputAction;

	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void CommAttack() override;
	
	
private:
	/**
	 * @brief 开启增强输入
	 */
	void InitEnhancedInput();

	virtual void MovementForEnhancedInput(const FInputActionValue& InputActionValue);

	virtual void RunningForEnhancedInput(const FInputActionValue& InputActionValue);

	virtual void AttackForEnhancedInput(const FInputActionValue& InputActionValue);
};
