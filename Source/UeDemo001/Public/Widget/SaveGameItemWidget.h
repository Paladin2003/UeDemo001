// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/GameSaveInfo.h"
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
	 * @brief 记录加载按钮
	 */
	UPROPERTY(meta=(BindWidget))
	class UButton* LoadBtn;

	/**
	 * @brief 记录删除按钮
	 */
	UPROPERTY(meta=(BindWidget))
	class UButton* DeleteBtn;
	
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

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	void InitGameSaveInfo(FGameSaveInfo InGameSaveInfo);	

private :

	UPROPERTY()
	FGameSaveInfo GameSaveInfo;

	UFUNCTION()
	void LoadGame();

	UFUNCTION()
	void DeleteGame();
	
	UFUNCTION()
	FText GetSlotName();

	UFUNCTION()
	FText GetLevel();

	UFUNCTION()
	FText GetSaveDate();

	UFUNCTION()
	FText GetTotalTime();
};
