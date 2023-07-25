// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SaveGameItemWidget.h"

#include "Components/TextBlock.h"

void USaveGameItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USaveGameItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SaveSlotTextBlock->TextDelegate.BindUFunction(this,"GetSlotName");
	SaveLevelTextBlock->TextDelegate.BindUFunction(this,"GetLevel");
	SaveDateTextBlock->TextDelegate.BindUFunction(this,"GetSaveDate");
	SaveTotalTimeTextBlock->TextDelegate.BindUFunction(this,"GetTotalTime");
}

FText USaveGameItemWidget::GetSlotName()
{
	UE_LOG(LogTemp,Warning,TEXT("GetSlotName..."));
	return FText::FromString(this->SaveSlotName);
}

FText USaveGameItemWidget::GetLevel()
{
	UE_LOG(LogTemp,Warning,TEXT("GetLevel..."));
	FFormatNamedArguments  NamedArguments;
	NamedArguments.Add(TEXT("Level"),this->SaveLevel);
	return FText::Format(NSLOCTEXT("","","Lv.{Level}"),NamedArguments);
}

FText USaveGameItemWidget::GetSaveDate()
{
	UE_LOG(LogTemp,Warning,TEXT("GetSaveDate..."));
	return FText::FromString(this->SaveDate);
}

FText USaveGameItemWidget::GetTotalTime()
{
	UE_LOG(LogTemp,Warning,TEXT("GetTotalTime..."));
	return FText::FromString(FString(TEXT("总时长：")) + FString::FromInt(this->SaveTotalTime));
}
