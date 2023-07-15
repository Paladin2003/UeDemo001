// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PostProcessComponent.h"
#include "GameFramework/Character.h"
#include "Missile/DemoBaseMissle.h"
#include "GameFramework/Actor.h"
#include "Widget/DamageTipWidget.h"
#include "DemoBaseCharacter.generated.h"

UCLASS()
class UEDEMO001_API ADemoBaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	ADemoBaseCharacter();

	/**
	 * @brief 持续攻击中
	 */
	bool bSustainedAttacking;

	/**
	 * @brief 死亡后延迟销毁时间
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init")
	float DestroyDelay = 2.5f;
	
	/**
	 * @brief 当前血量
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init")
	int32 CurHp = 10;
	/**
	 * @brief 最大血量
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init")
	int32 MaxHp = 10;

public:
	/**
	 * @brief 是否奔跑
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement")
	bool bIsRunning;

	/**
	 * @brief 是否死亡
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Movement")
	bool bIsDie;

	/**
	 * @brief 是否正在攻击
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attack")
	bool bAttacking;

	/**
	 * @brief 是否正在被攻击
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="move")
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

protected:

	/**
	 * @brief 伤害显示UI
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init")
	TSubclassOf<UDamageTipWidget> DamageTipWidget;

	/**
	 * @brief 武器
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Weapon;

	/**
	 * @brief 骨骼网格体的初始旋转 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init")
	FRotator DefaultRotateForSkm = FRotator(0, -90, 0);

	/**
	 * @brief 发射物类型
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Init")
	TSubclassOf<class ADemoBaseMissle> MissileClass;

	/**
	 * @brief 被攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Anim")
	class UAnimMontage* HitAnimMontage;

	/**
	 * @brief 普通攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Anim")
	class UAnimMontage* AttackAnimMontage;

	/**
	 * @brief 魔法攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Anim")
	class UAnimMontage* MagicAttackAnimMontage;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief 设置角色最大行走速度
	 * @param MaxWalkSpeed 
	 */
	virtual void SetCharacterMaxWalkSpeed(float MaxWalkSpeed);

protected:

	FTimerHandle TimerHandle;

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
	void CreateMagicFireBall(const int32 BallCount, const FVector& LocationEnd) const;

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

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

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
