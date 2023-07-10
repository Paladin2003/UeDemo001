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

	SetCharactorMaxWalkSpeed(300.f);
}
