#pragma once

#include "CoreMinimal.h"
#include "Engine/Datatable.h"
#include "CharacterInfo.generated.h"

USTRUCT(BlueprintType)
struct UEDEMO001_API FCharacterInfo: public FTableRowBase
{

	GENERATED_USTRUCT_BODY()
public:
	/**
	 * @brief 角色名称
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString Name = "Character01";

	/**
	 * @brief 角色等级
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 1,UIMin = 1,UIMax = 99))
	int32 Level = 1;

	/**
	 * @brief 当前经验值
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 CurExp = 0;

	/**
	 * @brief 最大经验值
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 MaxExp = 20;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 DieExp = 2;

	/**
	 * @brief 当前血量
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 CurHp = 10;

	/**
	 * @brief 最大血量
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 MaxHp = 10;

	/**
	 * @brief 当前魔法值
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 CurMp = 10;

	/**
	 * @brief 最大魔法值
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 MaxMp = 10;

	/**
	 * @brief 皮肤
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)	
	UMaterialInstance* Skin;

	/**
	 * @brief 生成时体型比例缩放
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0.1,UIMin = 0.1))
	float ScaleRate = 1.f;

	/**
	 * @brief 是否远程攻击
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bFarAttack = true;

	/**
	 * @brief 攻击范围
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0.5,UIMin = 0.5,Units = "m"))
	float AttackRange = 1.f;
};
