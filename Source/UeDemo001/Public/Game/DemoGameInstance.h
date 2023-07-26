// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Struct/GameSaveInfo.h"
#include "DemoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bIsLoad;

	UPROPERTY()
	FGameSaveInfo LoadGameInfo;
};
