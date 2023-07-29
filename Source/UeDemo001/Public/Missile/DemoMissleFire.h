// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Missile/DemoBaseMissle.h"
#include "DemoMissleFire.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoMissleFire : public ADemoBaseMissle
{
	GENERATED_BODY()

protected:

	virtual void MissileEffect(ADemoBaseCharacter* InCharacter) override;
};
