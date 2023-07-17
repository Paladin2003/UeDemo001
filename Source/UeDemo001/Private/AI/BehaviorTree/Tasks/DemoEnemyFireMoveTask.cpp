// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Tasks/DemoEnemyFireMoveTask.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Blueprint/AIAsyncTaskBlueprintProxy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Player/DemoDefaultPlayer.h"
#include "Character/Enemy/DemoDefaultEnemy.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UDemoEnemyFireMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	UE_LOG(LogTemp,Warning,TEXT("UDemoEnemyFireMoveTask::ExecuteTask。。。。"));
	if (UObject* Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Player")))
	{
		UE_LOG(LogTemp,Warning,TEXT("获取黑板player：%s"),*Object->GetName());	
	}
	ADemoDefaultPlayer* DefaultPlayer = Cast<ADemoDefaultPlayer>(UBTFunctionLibrary::GetBlackboardValueAsActor(this,Player));

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
		AAIController* AiController = OwnerComp.GetAIOwner();
		EPathFollowingRequestResult::Type RequestResult = AiController->MoveToActor(DefaultPlayer);
		// UAIAsyncTaskBlueprintProxy* Proxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(this,DefaultEnemy,FVector(),DefaultPlayer);

		if(RequestResult == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			return EBTNodeResult::Succeeded;
		}
	}
	return NodeResult;
}
