// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DemoCommBtnWidget.h"

void UDemoCommBtnWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp,Warning,TEXT("NativeConstruct..."));
}

void UDemoCommBtnWidget::NativeOnInitialized()
{
	UE_LOG(LogTemp,Warning,TEXT("NativeOnInitialized..."));
	Super::NativeOnInitialized();

	this->BtnTextBlock->SetText(FText::FromString(BtnName));

	this->BtnImage->SetBrushFromTexture(ImageTexture);
}
