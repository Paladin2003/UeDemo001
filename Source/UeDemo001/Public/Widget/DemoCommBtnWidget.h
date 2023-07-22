// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DemoCommBtnWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoCommBtnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidgetOptional))
	UTextBlock* BtnTextBlock;

	UPROPERTY(meta=(BindWidgetOptional))
	UImage* BtnImage;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString BtnName;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UTexture2D* ImageTexture;

	virtual void NativeOnInitialized() override;
};
