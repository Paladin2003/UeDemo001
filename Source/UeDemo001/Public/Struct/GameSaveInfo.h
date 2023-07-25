#pragma once

#include "CoreMinimal.h"
#include "CharacterInfo.h"
#include "GameSaveInfo.generated.h"

USTRUCT(BlueprintType)
struct UEDEMO001_API FGameSaveInfo
{

	GENERATED_USTRUCT_BODY()
	
public:

	FGameSaveInfo();

	UPROPERTY()
	FString SaveName;

	UPROPERTY()
	FString SaveDate;

	UPROPERTY()
	int32 TotalCostTime;

	UPROPERTY()
	FString ImagePath;

	UPROPERTY()
	FCharacterInfo CharacterInfo;
};
