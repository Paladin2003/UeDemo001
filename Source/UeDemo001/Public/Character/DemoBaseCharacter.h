// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Widget/DamageTipWidget.h"
#include "Components/TimelineComponent.h"
#include "Struct/CharacterInfo.h"
#include "DemoBaseCharacter.generated.h"

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsLockHp ;

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

	/**
	 * @brief 发起普通攻击
	 */
	virtual void CommAttack();

	virtual void DelayDestroy();

	/**
	 * @brief 获取角色信息
	 * @return 
	 */
	FCharacterInfo GetCharacterInfo();

protected:
	/**
	 * @brief 延迟销毁的计时器
	 */
	FTimerHandle DelayDestroyTimerHandle;

	/**
	 * @brief MP回复计时器
	 */
	FTimerHandle RecoverMpTimerHandle;

	/**
	 * @brief 冲刺时间轴
	 */
	FTimeline DashTimeLine;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void InitCharacterInfo();
	
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
	 * @brief 加速冲刺曲线
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init|param")
	UCurveFloat* DashCurve;

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
	void AutoRecoverMp();
	
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


	/**
	 * @brief 加速冲刺
	 * @param DurationTime 加速时长 
	 * @param DashRate 加速倍率
	 */
	virtual void TriggerTimeDash(const float DurationTime,const float DashRate = 2.0f);

	UFUNCTION()
	void OnDashTick();

	UFUNCTION()
	void OnDashFinished();

private:
	UFUNCTION()
	void ExecuteDelayDestroy();
};
