// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Tasks/DemoEnemyAttackTask.h"

#include "BehaviorTree/BTFunctionLibrary.h"
#include "Character/Enemy/DemoDefaultEnemy.h"
#include "Character/Player/DemoDefaultPlayer.h"

EBTNodeResult::Type UDemoEnemyAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//获取行为树控制的Character
	if (ADemoDefaultEnemy* DefaultEnemy = Cast<ADemoDefaultEnemy>(ActorOwner->GetInstigator()))
	{
		//是否已死亡
		if (DefaultEnemy->bIsDie)
		{
			return EBTNodeResult::Failed;
		}
		DefaultEnemy->CommAttack();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
