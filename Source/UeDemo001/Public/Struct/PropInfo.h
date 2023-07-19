#pragma once

#include "CoreMinimal.h"
#include "Engine/Datatable.h"
#include "PropInfo.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct UEDEMO001_API FPropInfo: public FTableRowBase
{

	GENERATED_USTRUCT_BODY()
public:
	/**
	 * @brief 道具名称
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString Name = "Prop001";

	/**
	 * @brief 道具粒子系统
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UNiagaraSystem* NiagaraSystem;
};
