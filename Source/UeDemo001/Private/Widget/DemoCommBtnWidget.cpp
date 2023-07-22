// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DemoCommBtnWidget.h"

void UDemoCommBtnWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	this->BtnTextBlock->SetText(FText::FromString(BtnName));

	this->BtnImage->SetBrushFromTexture(ImageTexture);
}
