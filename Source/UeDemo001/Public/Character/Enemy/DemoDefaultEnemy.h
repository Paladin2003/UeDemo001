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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

protected:
	virtual void BeginPlay() override;
};
