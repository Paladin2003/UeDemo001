// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveGameItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API USaveGameItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	/**
	 * @brief 记录图片
	 */
	UPROPERTY(meta=(BindWidget))
	class UImage* SaveImage;

	/**
	 * @brief 记录插槽
	 */
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* SaveSlotTextBlock;

	/**
	 * @brief 记录等级
	 */
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* SaveLevelTextBlock;

	/**
	 * @brief 记录日期
	 */
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* SaveDateTextBlock;

	/**
	 * @brief 记录总时长
	 */
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* SaveTotalTimeTextBlock;

	FString SaveImagePath;
	
	FString SaveSlotName;

	int32 SaveLevel;

	FString SaveDate;

	int32 SaveTotalTime;

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

private :

	UFUNCTION()
	FText GetSlotName();

	UFUNCTION()
	FText GetLevel();

	UFUNCTION()
	FText GetSaveDate();

	UFUNCTION()
	FText GetTotalTime();
};
