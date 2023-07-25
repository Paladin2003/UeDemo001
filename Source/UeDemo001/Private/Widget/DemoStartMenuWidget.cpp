// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DemoStartMenuWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Game/DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UDemoStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BtnBegin->Button->OnReleased.AddDynamic(this,&UDemoStartMenuWidget::StartGame);
	BtnContinue->Button->OnReleased.AddDynamic(this,&UDemoStartMenuWidget::ContinueGame);
	BtnSave->Button->OnReleased.AddDynamic(this,&UDemoStartMenuWidget::SaveGame);
	BtnExit->Button->OnReleased.AddDynamic(this,&UDemoStartMenuWidget::ExitGame);
}

void UDemoStartMenuWidget::StartGame()
{
	// UE_LOG(LogTemp,Warning,TEXT("开始游戏。。。。"));
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),GameDefaultLevel);
}

void UDemoStartMenuWidget::ContinueGame()
{
	Switcher->SetActiveWidgetIndex(1);
	if (UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(GetWorld()->GetGameInstance()))
	{
		// GameInstance->bIsLoadGame = true;
		// UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),GameDefaultLevel);
	}

	
}

void UDemoStartMenuWidget::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),GetOwningPlayer(),EQuitPreference::Quit,false);
}

void UDemoStartMenuWidget::SaveGame()
{
	UE_LOG(LogTemp,Warning,TEXT("保存游戏。。。。"));
}
