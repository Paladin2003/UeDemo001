#pragma once

#include "CoreMinimal.h"
#include "CharacterState.generated.h"

USTRUCT(BlueprintType)
struct UEDEMO001_API FCharacterState
{

	GENERATED_USTRUCT_BODY()
public:
	FCharacterState();

	FCharacterState(int32 Hp,int32 Mp);
		
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
	 * @brief MP恢复速率，每几秒恢复一次
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	float MpAutoRecoverRate = 1.f;

	/**
	* @brief MP每次恢复量
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(ClampMin = 0,UIMin = 0))
	float MpAutoRecoverPoint = 1.f;
	
	/**
	 * @brief 攻击范围
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(ClampMin = 0.5,UIMin = 0.5,Units = "cm"))
	float AttackRange = 1.f;

	/**
	 * @brief 行走速度
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(UIMin = 100))
	float WalkSpeed = 500.f;

	FCharacterState& operator+=(const FCharacterState& InState);
};
