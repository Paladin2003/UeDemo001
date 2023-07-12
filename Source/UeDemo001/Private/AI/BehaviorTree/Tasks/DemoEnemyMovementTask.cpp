// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Tasks/DemoEnemyMovementTask.h"

#include "Character/DemoBaseCharacter.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Enemy/DemoDefaultEnemy.h"

EBTNodeResult::Type UDemoEnemyMovementTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//获取行为树控制的Character
	if(ADemoDefaultEnemy* BaseCharacter = Cast<ADemoDefaultEnemy>(ActorOwner->GetInstigator()))
	{
		//是否已死亡
		if(BaseCharacter->bIsDie)
		{
			return EBTNodeResult::Failed;
		}
		
		if(const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			FNavLocation RandomLocation;
			//获取随位置
			if(NavSystem -> GetRandomReachablePointInRadius(BaseCharacter->GetActorLocation(),500.f,RandomLocation))
			{
				//寻路
				UAIBlueprintHelperLibrary::CreateMoveToProxyObject(nullptr, BaseCharacter, RandomLocation.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;;
}
