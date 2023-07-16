// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Missile/DemoBaseMissle.h"
#include "GameFramework/Actor.h"
#include "Widget/DamageTipWidget.h"
#include "DemoBaseCharacter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_USTRUCT_BODY()
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
};

UCLASS()
class UEDEMO001_API ADemoBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADemoBaseCharacter();
	
	/**
	 * @brief 持续攻击中
	 */
	bool bSustainedAttacking;
	
	/**
	 * @brief 是否奔跑
	 */
	bool bIsRunning;

	/**
	 * @brief 是否死亡
	 */
	bool bIsDie;

	/**
	 * @brief 是否正在攻击
	 */
	bool bAttacking;

	/**
	 * @brief 是否正在被攻击
	 */
	bool bIsHit;

	/**
	 * @brief 普通攻击结束后的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AttackEndNotify();

	/**
	 * @brief 被攻击后完成的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void HitEndNotify();
	
	/**
	 * @brief 普通攻击时触发发射物的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AttackFireBall();

	/**
	 * @brief 设置角色最大行走速度
	 * @param MaxWalkSpeed 
	 */
	virtual void SetCharacterMaxWalkSpeed(float MaxWalkSpeed);

	FCharacterInfo GetCharacterInfo();

protected:

	FTimerHandle TimerHandle;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief 经验值计算
	 * @param InExp 
	 */
	virtual void CalculateExp(int32 InExp);

	/**
	 * @brief 升级
	 * @param LastLevelOverExp 上级溢出经验，即升级后剩余经验 
	 * @return 升级后等级
	 */
	virtual int32 LevelUp(const int32 LastLevelOverExp);

	/**
	 * @brief 角色状态信息
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Init|Info",meta=(DisplayPriority = 0))
	FCharacterInfo CharacterInfo;

	/**
	 * @brief 死亡后延迟销毁时间
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|param",meta=(DisplayPriority = 2))
	float DestroyDelay = 2.5f;

	/**
	 * @brief 死亡后能提供的经验值
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|param",meta=(DisplayPriority = 2))
	int32 ExpValue = 2;

	/**
	 * @brief 发射物类型
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|Damage",meta=(DisplayPriority = 3))
	TSubclassOf<class ADemoBaseMissle> MissileClass;

	/**
	 * @brief 伤害显示UI
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|UI",meta=(DisplayPriority = 4))
	TSubclassOf<UDamageTipWidget> DamageTipWidget;

	/**
	 * @brief 被攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|Anim",meta=(DisplayPriority = 5))
	class UAnimMontage* HitAnimMontage;

	/**
	 * @brief 普通攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|Anim",meta=(DisplayPriority = 5))
	class UAnimMontage* AttackAnimMontage;

	/**
	 * @brief 魔法攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|Anim",meta=(DisplayPriority = 5))
	class UAnimMontage* MagicAttackAnimMontage;
	
	/**
	 * @brief 骨骼网格体的初始旋转 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|componet",meta=(DisplayPriority = 6))
	FRotator DefaultRotateForSkm = FRotator(0, -90, 0);
	
	/**
	 * @brief 武器
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Weapon;
	
	/**
	 * @brief 延时销毁
	 */
	UFUNCTION()
	void DelayDestroyed();
	/**
	 * @brief 发起普通攻击
	 */
	virtual void CommAttack();

	/**
	 * @brief 魔法攻击生成
	 * @param BallCount 
	 * @param LocationEnd 
	 */
	void CreateMagicFireBall(const int32 BallCount, const FVector& LocationEnd);

	/**
	 * @brief 发起魔法攻击
	 */
	virtual void MagicAttack();

	/**
	 * @brief 根据鼠标获取攻击点
	 * @return 
	 */
	FVector GetAttackPointByMouse() const;
	
	/**
	 * @brief 攻击前转身面对攻击点
	 */
	void RotateBeforeAttack();

	/**
	 * @brief 处理伤害事件
	 * @param DamageAmount 
	 * @param DamageEvent 
	 * @param EventInstigator 
	 * @param DamageCauser 
	 * @return 
	 */
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
};
