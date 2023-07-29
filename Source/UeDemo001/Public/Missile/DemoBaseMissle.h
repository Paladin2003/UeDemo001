// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DemoBaseCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DemoBaseMissle.generated.h"

UCLASS()
class UEDEMO001_API ADemoBaseMissle : public AActor
{
	GENERATED_BODY()

public:

	ADemoBaseMissle();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UProjectileMovementComponent* Movement;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystemComponent* Particle;

protected:

	FTimerHandle FireTimerHandle;

	ADemoBaseCharacter* DamagedCharacter;

	/**
	 * @brief 伤害值
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damage")
	int32 Damage = 3;
	/**
	 * @brief 异常状态伤害值
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damage")
	int32 DebuffDamage = 1;
	/**
	 * @brief 异常状态时间
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damage")
	float DebuffTime = 1.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystem* BoomParticle;

	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * @brief 发射物的效果结算
	 * @param InCharacter 
	 */
	virtual void MissileEffect(ADemoBaseCharacter* InCharacter);

	/**
	 * @brief 效果影响的回调
	 */
	UFUNCTION()
	virtual void EffectInvoke();
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DestroyDelayTime;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

private:
	bool bOverlapped = false;
};
