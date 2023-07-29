// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Missile/DemoBaseMissle.h"
#include "DemoMissleIce.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoMissleIce : public ADemoBaseMissle
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Damage")
	float SlowDownRate = 0.5f;
	
	virtual void MissileEffect(ADemoBaseCharacter* InCharacter) override;

	
};
