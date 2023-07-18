// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Tasks/DemoEnemyMoveTo.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/DemoDefaultEnemy.h"
#include "GameFramework/PawnMovementComponent.h"

EBTNodeResult::Type UDemoEnemyMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ADemoDefaultEnemy* DefaultEnemy = Cast<ADemoDefaultEnemy>(OwnerComp.GetAIOwner()->GetCharacter()))
	{
		if(DefaultEnemy->bIsDie)
		{
			DefaultEnemy->GetMovementComponent()->StopActiveMovement();
			return EBTNodeResult::Failed;
		}
		
		this->AcceptableRadius = DefaultEnemy->GetCharacterInfo().AttackRange;	
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
