// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoCommBtnWidget.h"
#include "Blueprint/UserWidget.h"
#include "DemoStartMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UDemoCommBtnWidget* BtnBegin;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UDemoCommBtnWidget* BtnSave;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UDemoCommBtnWidget* BtnExit;


	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void SaveGame();
};
