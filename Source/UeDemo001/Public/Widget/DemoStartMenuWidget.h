// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCommBtnWidget.h"
#include "Blueprint/UserWidget.h"
#include "SaveGameListWidget.h"
#include "DemoStartMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* Switcher;
	
	UPROPERTY(meta=(BindWidget))
	UDemoCommBtnWidget* BtnBegin;

	UPROPERTY(meta=(BindWidget))
	UDemoCommBtnWidget* BtnContinue;

	UPROPERTY(meta=(BindWidget))
	UDemoCommBtnWidget* BtnSave;

	UPROPERTY(meta=(BindWidget))
	UDemoCommBtnWidget* BtnExit;

	UPROPERTY(meta=(BindWidget))
	USaveGameListWidget* GameSaveList;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSoftObjectPtr<UWorld> GameDefaultLevel;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void ContinueGame();

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void SaveGame();
};
