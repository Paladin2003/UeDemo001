// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/DemoDefaultEnemy.h"
#include "AI/Controller/DemoEnemyAIController.h"

ADemoDefaultEnemy::ADemoDefaultEnemy()
{
	AIControllerClass = ADemoEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ADemoDefaultEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ADemoDefaultEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(nullptr != EnemyData)
	{
		for (auto DataRow : EnemyData->GetRowMap())
		{
			FName& RowName = DataRow.Key;
			/*UE_LOG(LogTemp,Warning,TEXT("设置的怪物名：%s==比对的怪物名:%s,二者比较的结果：%d"),
				*EnemyName,*RowName.ToString(),(EnemyName == RowName.ToString()));*/
			if(EnemyName == RowName.ToString())
			{
				this->CharacterInfo = *reinterpret_cast<FCharacterInfo*>(DataRow.Value);

				InitCharacterInfo();
				break;
			}
		}
	}
}
