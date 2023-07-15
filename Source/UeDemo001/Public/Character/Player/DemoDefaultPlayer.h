// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Character/DemoBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
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
	
	FTimeline TimeLine;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USpringArmComponent* CameraArm;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCurveFloat* FloatCurve;
	
	/**
	 * @brief 后期盒子组件
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPostProcessComponent* PostProcess;

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


	/**
	* @brief 攻击输入
	*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Enhanced Input")
	TObjectPtr<UInputAction> MagicAttackInputAction;
	
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void CommAttack() override;

	UFUNCTION()
	void SustainedAttackPostBlendCallBack();

	UFUNCTION()
	void SustainedAttackPostBlendFinishedCallBack();
	
	
private:
	/**
	 * @brief 开启增强输入
	 */
	void InitEnhancedInput();

	/**
	 * @brief 移动输入
	 * @param InputActionValue 
	 */
	virtual void MovementForEnhancedInput(const FInputActionValue& InputActionValue);

	/**
	 * @brief 走/跑切换输入
	 * @param InputActionValue 
	 */
	virtual void RunningForEnhancedInput(const FInputActionValue& InputActionValue);

	/**
	 * @brief 普通攻击输入
	 * @param InputActionValue 
	 */
	virtual void AttackForEnhancedInput(const FInputActionValue& InputActionValue);

	/**
	 * @brief 魔法攻击输入
	 * @param InputActionValue 
	 */
	virtual void MagicAttackForEnhancedInput(const FInputActionValue& InputActionValue);

	/**
	 * @brief 结束魔法攻击输入
	 * @param InputActionValue 
	 */
	virtual void EndMagicAttackForEnhancedInput(const FInputActionValue& InputActionValue);
};
