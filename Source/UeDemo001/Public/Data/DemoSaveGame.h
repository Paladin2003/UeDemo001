// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Struct/CharacterInfo.h"
#include "Struct/GameSaveInfo.h"
#include "DemoSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FGameSaveInfo> GameSaveInfos = {};

	UFUNCTION(BlueprintCallable,meta=(WorldContext = "WorldContextObject"))
	static void AddNewSave(UObject* WorldContextObject,FCharacterInfo InCharacterInfo,FString InSaveName);

	TArray<FGameSaveInfo> GetAllGameSaved();
};
