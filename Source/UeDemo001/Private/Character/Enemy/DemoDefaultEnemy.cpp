// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/DemoDefaultEnemy.h"
#include "AI/Controller/DemoEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Player/DemoDefaultPlayer.h"
#include "Game/DemoGameInstance.h"

ADemoDefaultEnemy::ADemoDefaultEnemy()
{
	AIControllerClass = ADemoEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ADemoDefaultEnemy::OnPerceptionUpdated);
	PerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this,&ADemoDefaultEnemy::OnTargetPerceptionForgotten);

	PerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this,&ADemoDefaultEnemy::OnTargetPerceptionInfoUpdated);
}

void ADemoDefaultEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ADemoDefaultEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (nullptr != EnemyData)
	{
		for (auto DataRow : EnemyData->GetRowMap())
		{
			FName& RowName = DataRow.Key;
			/*UE_LOG(LogTemp,Warning,TEXT("设置的怪物名：%s==比对的怪物名:%s,二者比较的结果：%d"),
				*EnemyName,*RowName.ToString(),(EnemyName == RowName.ToString()));*/
			if (EnemyName == RowName.ToString())
			{
				this->CharacterInfo = *reinterpret_cast<FCharacterInfo*>(DataRow.Value);

				InitCharacterInfo();
				break;
			}
		}
	}
}

void ADemoDefaultEnemy::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s的AI感知到%d个单位"), *FName(this->GetName()).ToString(), UpdatedActors.Num());
	for(AActor* Actor: UpdatedActors)
	{
		if( ADemoDefaultPlayer* DefaultPlayer = Cast<ADemoDefaultPlayer>(Actor))
		{
			/*UE_LOG(LogTemp,Warning,TEXT("%s感知到玩家类型对象：%s"),*FName(this->GetName()).ToString(),
				*FName(DefaultPlayer->GetName()).ToString());*/
			//设置黑板值
			UBlackboardComponent* BlackboardComponent = UAIBlueprintHelperLibrary::GetBlackboard(this);
			BlackboardComponent->SetValueAsObject("Player",DefaultPlayer);
			break;
		}
	}
}

void ADemoDefaultEnemy::OnTargetPerceptionForgotten(AActor* Actor)
{
	// UE_LOG(LogTemp,Warning,TEXT("%s已超出%s的感知范围。。。"),*FName(Actor->GetName()).ToString(),*FName(this->GetName()).ToString());
	
}

void ADemoDefaultEnemy::OnTargetPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	// UE_LOG(LogTemp,Warning,TEXT("OnTargetPerceptionInfoUpdated。。。"));
}
