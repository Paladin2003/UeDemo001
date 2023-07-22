// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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
	UPROPERTY(meta=(BindWidget))
	UTextBlock* BtnTextBlock;

	UPROPERTY(meta=(BindWidget))
	UImage* BtnImage;

	UPROPERTY(meta=(BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString BtnName;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UTexture2D* ImageTexture;

	virtual void NativeConstruct() override;
	
	virtual void NativeOnInitialized() override;
};
