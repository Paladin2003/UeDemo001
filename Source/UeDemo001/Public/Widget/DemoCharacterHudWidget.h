// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoCharacterHudWidget.generated.h"

class ADemoBaseCharacter;
class UProgressBar;
/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoCharacterHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerPlayer(ADemoBaseCharacter* PlayerIn);
	void BindWidgetPoint();

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidgetOptional))
	UProgressBar* HP;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidgetOptional))
	UProgressBar* MP;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidgetOptional))
	UProgressBar* Exp;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidgetOptional))
	class UTextBlock* Level;

private:

	ADemoBaseCharacter* Player;
	
	UFUNCTION()
	FText GetLevel() const;

	UFUNCTION()
	float GetHpRate() const;
	
	UFUNCTION()
	float GetMpRate() const;

	UFUNCTION()
	float GetExpRate() const;
};
