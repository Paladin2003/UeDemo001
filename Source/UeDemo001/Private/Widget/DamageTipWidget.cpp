// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageTipWidget.h"

void UDamageTipWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(DamageTipAnim);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&UDamageTipWidget::AutoDestroyed,HealthTime,false);
}

void UDamageTipWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DamageTip->TextDelegate.BindUFunction(this, "GetDamageValue");
}

FText UDamageTipWidget::GetDamageValue() const
{
	return FText::AsNumber(DamageValue);
}

void UDamageTipWidget::AutoDestroyed()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	RemoveFromParent();
}
