// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Tasks/DemoEnemyFireMoveTask.h"

#include "BehaviorTree/BTFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Player/DemoDefaultPlayer.h"
#include "Character/Enemy/DemoDefaultEnemy.h"

EBTNodeResult::Type UDemoEnemyFireMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ADemoDefaultPlayer* DefaultPlayer = Cast<ADemoDefaultPlayer>(UBTFunctionLibrary::GetBlackboardValueAsActor(this,Player));

	if(nullptr == DefaultPlayer)
	{
		return EBTNodeResult::Failed;
	}
	
	//获取行为树控制的Character
	if (ADemoDefaultEnemy* DefaultEnemy = Cast<ADemoDefaultEnemy>(ActorOwner->GetInstigator()))
	{
		//是否已死亡
		if (DefaultEnemy->bIsDie)
		{
			return EBTNodeResult::Failed;
		}
		//寻路
		UAIBlueprintHelperLibrary::CreateMoveToProxyObject(nullptr, DefaultEnemy, DefaultPlayer->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
