// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	/**
	 * @brief 是否奔跑
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Movement")
	bool bIsRunning;

	/**
	 * @brief 是否死亡
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Movement")
	bool bIsDie;

	/**
	 * @brief 是否正在攻击
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Attack")
	bool bAttacking;

	/**
	 * @brief 是否正在被攻击
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="move")
	bool bIsHit;
	
	/**
	 * @brief 攻击后的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AttackEndNotify();

	/**
	 * @brief 被攻击后完成的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void HitEndNotify();
	/**
	 * @brief 攻击时产生发射物的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AttackFireBall();

protected:

	bool bLockRotate;
	/**
	 * @brief 当前血量
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Init")
	int32 CurHp = 10;
	/**
	 * @brief 最大血量
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Init")
	int32 MaxHp = 10;

	/**
	 * @brief 伤害显示UI
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Init")
	TSubclassOf<UDamageTipWidget> DamageTipWidget;
	
	/**
	 * @brief 武器
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* Weapon;

	/**
	 * @brief 骨骼网格体的初始旋转 
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Init")
	FRotator DefaultRotateForSkm = FRotator(0,-90,0);

	/**
	 * @brief 发射物类型
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Init")
	TSubclassOf<class ADemoBaseMissle> MissileClass;

	/**
	 * @brief 被攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Anim")
	class UAnimMontage* HitAnimMontage;

	/**
	 * @brief 普通攻击动画蒙太奇
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Anim")
	class UAnimMontage* AttackAnimMontage;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetCharactorMaxWalkSpeed(float MaxWalkSpeed);
	
protected:
	/**
	 * @brief 发起普通攻击
	 */
	virtual void CommAttack();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
