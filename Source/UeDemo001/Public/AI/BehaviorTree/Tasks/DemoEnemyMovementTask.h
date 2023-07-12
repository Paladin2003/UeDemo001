// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "DemoEnemyMovementTask.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoEnemyMovementTask : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
protected:
	

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
