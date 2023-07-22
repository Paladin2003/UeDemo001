// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DemoStartMenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"

void UDemoStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BtnBegin->Button->OnReleased.AddDynamic(this,&UDemoStartMenuWidget::StartGame);
	BtnSave->Button->OnReleased.AddDynamic(this,&UDemoStartMenuWidget::StartGame);
	BtnExit->Button->OnReleased.AddDynamic(this,&UDemoStartMenuWidget::ExitGame);
}

void UDemoStartMenuWidget::StartGame()
{
	UE_LOG(LogTemp,Warning,TEXT("开始游戏。。。。"));
}

void UDemoStartMenuWidget::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),GetOwningPlayer(),EQuitPreference::Quit,false);
}

void UDemoStartMenuWidget::SaveGame()
{
	UE_LOG(LogTemp,Warning,TEXT("保存游戏。。。。"));
}