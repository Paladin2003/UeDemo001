// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Missile/DemoBaseMissle.h"
#include "DemoMissleTornado.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoMissleTornado : public ADemoBaseMissle
{
	GENERATED_BODY()

protected:

	FTimerHandle TornadoTimerHandle;
	
	virtual void MissileEffect(ADemoBaseCharacter* InCharacter) override;

	virtual void EffectInvoke() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void TornadoInvoke();
};
