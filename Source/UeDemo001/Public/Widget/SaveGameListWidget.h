// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveGameListWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API USaveGameListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* Container;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TSubclassOf<class USaveGameItemWidget> SaveGameItemWidget;
	
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
};
