// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DamageTipWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDamageTipWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ExposeOnSpawn = 1))
	int32 DamageValue = 0;

	UPROPERTY(BlueprintReadOnly, Transient,meta=(BindWidgetAnimOptional))
	UWidgetAnimation* DamageTipAnim;
	
protected:

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float HealthTime = 1.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidgetOptional))
	UTextBlock* DamageTip;

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	/**
	 * @brief 绑定伤害值到文本控件
	 * @return 
	 */
	UFUNCTION()
	FText GetDamageValue();

	/**
	 * @brief 自动销毁回调
	 */
	UFUNCTION()
	void AutoDestroyed();
};
