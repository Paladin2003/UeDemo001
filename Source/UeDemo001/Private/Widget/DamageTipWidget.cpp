// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageTipWidget.h"

void UDamageTipWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(DamageTipAnim);
}

void UDamageTipWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DamageTip->TextDelegate.BindUFunction(this,"GetDamageValue");
}

FText UDamageTipWidget::GetDamageValue()
{
	return FText::AsNumber(DamageValue);
}
