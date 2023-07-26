// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SaveGameItemWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Game/DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"

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
	SaveBtn->OnReleased.AddDynamic(this,&USaveGameItemWidget::LoadGame);
}

void USaveGameItemWidget::InitGameSaveInfo(FGameSaveInfo InGameSaveInfo)
{
	this->GameSaveInfo = InGameSaveInfo;
}

void USaveGameItemWidget::LoadGame()
{
	UE_LOG(LogTemp,Warning,TEXT("读取游戏。。。。"));

	if (UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(GetWorld()->GetGameInstance()))
	{
		GameInstance->bIsLoad = true;
		GameInstance->LoadGameInfo = this->GameSaveInfo;

		UGameplayStatics::OpenLevel(GetWorld(),TEXT("DefaultMap"));
	}
	
}

FText USaveGameItemWidget::GetSlotName()
{
	return FText::FromString(this->GameSaveInfo.SaveName);
}

FText USaveGameItemWidget::GetLevel()
{
	FFormatNamedArguments  NamedArguments;
	NamedArguments.Add(TEXT("Level"),this->GameSaveInfo.CharacterInfo.Level);
	return FText::Format(NSLOCTEXT("","","Lv.{Level}"),NamedArguments);
}

FText USaveGameItemWidget::GetSaveDate()
{
	return FText::FromString(this->GameSaveInfo.SaveDate);
}

FText USaveGameItemWidget::GetTotalTime()
{
	return FText::FromString(FString(TEXT("游戏时长：")) + FString::FromInt(this->GameSaveInfo.TotalCostTime));
}
