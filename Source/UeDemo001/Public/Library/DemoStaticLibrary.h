// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DemoStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoStaticLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief 保存游戏
	 */
	UFUNCTION(BlueprintCallable,Category="DemoStaticLibrary")
	static void SaveGame(class UDemoSaveGame* SaveGame);

	/**
	 * @brief 加载游戏
	 */
	UFUNCTION(BlueprintCallable,Category="DemoStaticLibrary")
	static class UDemoSaveGame* LoadGame();
};
