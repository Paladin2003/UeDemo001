// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/DemoDefaultEnemy.h"

#include "AI/Controller/DemoEnemyAIController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/DamageTipWidget.h"

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

float ADemoDefaultEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float Damage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	this->CurHp -= Damage;
	UE_LOG(LogTemp,Warning,TEXT("敌方【%s】受到%f点伤害,当前血量：%d/%d"),*FName(this->GetName()).ToString(),Damage,CurHp,MaxHp);
	UDamageTipWidget* TipWidget = CreateWidget<UDamageTipWidget>(GetWorld(),DamageTipWidget);
	TipWidget->DamageValue = Damage;
	TipWidget->AddToViewport(0);
	FVector2D ScreenPosition ;
	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(),GetActorLocation(),ScreenPosition);
	TipWidget->SetPositionInViewport(ScreenPosition);
	return Damage;
}
