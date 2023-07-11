// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DemoEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoEnemyAIController : public AAIController
{
	GENERATED_BODY()

	ADemoEnemyAIController();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
