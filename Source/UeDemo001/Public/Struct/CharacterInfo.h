#pragma once

#include "CoreMinimal.h"
#include "CharacterState.h"
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

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FCharacterState State;

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

	/**
	 * @brief 死亡后提供的经验值
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	int32 DieExp = 2;
	
	/**
	 * @brief 生成时体型缩放比例
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0.1,UIMin = 0.1))
	float ScaleRate = 1.f;

	/**
	 * @brief 是否远程攻击
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bFarAttack = true;

	/**
	 * @brief 死亡后延迟销毁时间
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(ClampMin = 0,UIMin = 0,Units = "s"))
	float DestroyDelay = 2.5f;

	/**
	 * @brief 发射物类型
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(DisplayThumbnail))
	TSubclassOf<class ADemoBaseMissle> MissileClass;

	/**
	 * @brief 普通攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage* AttackAnimMontage;

	/**
	 * @brief 普通攻击动画蒙太奇播放速率
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	float AttackAnimMontageRate = 1.25f;

	/**
	 * @brief 皮肤
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)	
	UMaterialInstance* Skin;

};
