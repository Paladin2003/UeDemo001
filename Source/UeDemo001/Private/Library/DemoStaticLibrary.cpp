// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/DemoStaticLibrary.h"

#include "Data/DemoSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UDemoStaticLibrary::SaveGame(UDemoSaveGame* SaveGame)
{
	UGameplayStatics::SaveGameToSlot(SaveGame,"DefaultSave",0);
}

UDemoSaveGame* UDemoStaticLibrary::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist("DefaultSave",0))
	{
		return Cast<UDemoSaveGame>(UGameplayStatics::LoadGameFromSlot("DefaultSave",0));
	}
	UE_LOG(LogTemp,Warning,TEXT("暂无存档。。"));
	return nullptr;
}
