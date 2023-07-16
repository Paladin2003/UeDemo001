// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/DemoCharacterHudWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Character/DemoBaseCharacter.h"

void UDemoCharacterHudWidget::SetOwnerPlayer(ADemoBaseCharacter* PlayerIn)
{
	this->Player = PlayerIn;
}

void UDemoCharacterHudWidget::BindWidgetPoint()
{
	Level->TextDelegate.BindUFunction(this,"GetLevel");
	HP->PercentDelegate.BindUFunction(this,"GetHpRate");
	MP->PercentDelegate.BindUFunction(this,"GetMpRate");
	Exp->PercentDelegate.BindUFunction(this,"GetExpRate");
}

void UDemoCharacterHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BindWidgetPoint();
}

FText UDemoCharacterHudWidget::GetLevel() const
{
	return FText::AsNumber(Player->GetCharacterInfo().Level);
}

float UDemoCharacterHudWidget::GetHpRate() const
{
	return  Player->GetCharacterInfo().CurHp * (1.0f) / Player->GetCharacterInfo().MaxHp;
}

float UDemoCharacterHudWidget::GetMpRate() const
{
	return  Player->GetCharacterInfo().CurMp * (1.0f) / Player->GetCharacterInfo().MaxMp;
}

float UDemoCharacterHudWidget::GetExpRate() const
{
	return  Player->GetCharacterInfo().CurExp * (1.0f) / Player->GetCharacterInfo().MaxExp;
}
