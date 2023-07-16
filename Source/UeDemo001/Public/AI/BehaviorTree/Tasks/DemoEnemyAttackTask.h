// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "DemoEnemyAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API UDemoEnemyAttackTask : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FBlackboardKeySelector Player;

protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
