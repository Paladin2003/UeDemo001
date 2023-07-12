// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/DemoEnemyAIController.h"

#include "Character/Enemy/DemoDefaultEnemy.h"

ADemoEnemyAIController::ADemoEnemyAIController()
{
}

void ADemoEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (nullptr != Cast<ADemoDefaultEnemy>(GetCharacter()))
	{
		ADemoDefaultEnemy* DemoDefaultEnemy = Cast<ADemoDefaultEnemy>(GetCharacter());
		if (!DemoDefaultEnemy->bIsDie)
		{
			UBehaviorTree* BehaviorTree = DemoDefaultEnemy->BehaviorTree;
			RunBehaviorTree(BehaviorTree);
			UE_LOG(LogTemp,Warning,TEXT("运行行为树：%s"),*FName(BehaviorTree->GetName()).ToString());	
		}
	}
}

void ADemoEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
