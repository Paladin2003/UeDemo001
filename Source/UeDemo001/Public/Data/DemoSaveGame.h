// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Struct/CharacterInfo.h"
#include "DemoSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FCharacterInfo CharacterInfo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	double GameCostTime = 0l;
};
