// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SaveGameListWidget.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Data/DemoSaveGame.h"
#include "Library/DemoStaticLibrary.h"
#include "Widget/SaveGameItemWidget.h"

void USaveGameListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UDemoSaveGame* SaveGame = UDemoStaticLibrary::LoadGame())
	{
		UE_LOG(LogTemp,Warning,TEXT("读取到存档。。。"));
		if(const TArray<FGameSaveInfo> GameSaveInfos = SaveGame->GetAllGameSaved(); GameSaveInfos.Num() > 0)
		{
			UE_LOG(LogTemp,Warning,TEXT("读取到存档记录%d条。。。"),GameSaveInfos.Num());
			for(FGameSaveInfo SaveInfo : GameSaveInfos)
			{
				UE_LOG(LogTemp,Warning,TEXT("读取中。。。"));
				USaveGameItemWidget* SaveItem = CreateWidget<USaveGameItemWidget>(this,SaveGameItemWidget);
				SaveItem->InitGameSaveInfo(SaveInfo);
				this->Container->AddChildToVerticalBox(SaveItem);
			}
		}
	}
}

void USaveGameListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}
