// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DemoSaveGame.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Library/CaptureScreenHelper.h"
#include "Library/DemoStaticLibrary.h"

void UDemoSaveGame::AddNewSave(UObject* WorldContextObject,FCharacterInfo InCharacterInfo,FString InSaveName)
{
	/*FString JSONCharacter;
	FJsonObjectConverter::UStructToJsonObjectString(InCharacterInfo, JSONCharacter, 0, 0);*/
	
	//截图
	UCaptureScreenHelper* CaptureScreenHelper = UCaptureScreenHelper::CaptureScreen(WorldContextObject,
		InCharacterInfo.Name + FDateTime::Now().ToFormattedString(*FString("_%Y%m%d%H%M%S")),
		EImageFormatType::PNG,100,100);
	
	UDemoSaveGame* DemoSaveGameInstance = UDemoStaticLibrary::LoadGame();
	if (nullptr == DemoSaveGameInstance)
	{
		DemoSaveGameInstance = NewObject<UDemoSaveGame>();
	}
	int32 InTotalCostTime = UKismetSystemLibrary::GetGameTimeInSeconds(WorldContextObject);
	
	FGameSaveInfo SaveInfo = FGameSaveInfo();
	SaveInfo.CharacterInfo = InCharacterInfo;
	SaveInfo.SaveName = InSaveName;
	SaveInfo.ImagePath = CaptureScreenHelper->GetImageName();
	if(DemoSaveGameInstance->GameSaveInfos.Num() > 0)
	{
		SaveInfo.TotalCostTime = InTotalCostTime + DemoSaveGameInstance->GameSaveInfos.Last().TotalCostTime;
	}else
	{
		SaveInfo.TotalCostTime = InTotalCostTime;	
	}
	DemoSaveGameInstance->GameSaveInfos.Add(SaveInfo);
	UDemoStaticLibrary::SaveGame(DemoSaveGameInstance);
}

TArray<FGameSaveInfo> UDemoSaveGame::GetAllGameSaved()
{
	if (const UDemoSaveGame* DemoSaveGameInstance = UDemoStaticLibrary::LoadGame(); nullptr == DemoSaveGameInstance)
	{
		return DemoSaveGameInstance->GameSaveInfos;
	}
	return GameSaveInfos;	
}
