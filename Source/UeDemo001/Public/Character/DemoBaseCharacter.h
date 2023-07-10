// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Missile/DemoBaseMissle.h"
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
	 * @brief 移动速率
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Movement")
	float MovementRate;
	
	/**
	 * @brief 是否正在攻击
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Attack")
	bool bAttacking;
	
protected:
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

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/**
	 * @brief 攻击后的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AttackEndNotify();

	/**
	 * @brief 攻击时产生发射物的通知
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AttackFireBall();
protected:
	/**
	 * @brief 发起普通攻击
	 */
	virtual void CommAttack();
	
	/**
	 * @brief 角色旋转
	 * @param Vector 移动向量
	 */
	void CharacterRotate(FVector Vector);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
