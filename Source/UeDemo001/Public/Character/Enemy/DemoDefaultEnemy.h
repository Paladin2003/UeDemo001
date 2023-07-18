// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/DemoBaseCharacter.h"
#include "DemoDefaultEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoDefaultEnemy : public ADemoBaseCharacter
{
	GENERATED_BODY()

	ADemoDefaultEnemy();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Init|AI",meta=(DisplayPriority = 7))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Init|Data",meta=(DisplayPriority = 1))
	UDataTable* EnemyData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generate")
	FString EnemyName = "Enemy001";

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UAIPerceptionComponent* PerceptionComponent;

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
};
