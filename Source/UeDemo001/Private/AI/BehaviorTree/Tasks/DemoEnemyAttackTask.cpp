// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Tasks/DemoEnemyAttackTask.h"

#include "BehaviorTree/BTFunctionLibrary.h"
#include "Character/Enemy/DemoDefaultEnemy.h"
#include "Character/Player/DemoDefaultPlayer.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UDemoEnemyAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

		if(const double Distance = UKismetMathLibrary::Vector_Distance(DefaultEnemy->GetActorLocation(),DefaultPlayer->GetActorLocation()); Distance <= 100)
		{
			DefaultEnemy->CommAttack();
			return EBTNodeResult::Succeeded;
		}else
		{
			return EBTNodeResult::Failed;
		}
	}
	return EBTNodeResult::Failed;
}
