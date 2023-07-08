// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Character/DemoBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "DemoDefaultPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoDefaultPlayer : public ADemoBaseCharacter
{
	GENERATED_BODY()

	ADemoDefaultPlayer();

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USpringArmComponent* CameraArm;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCameraComponent* Camera;

	virtual void BeginPlay() override;
	

private:
	/**
	 * @brief 开启增强输入
	 */
	void InitEnhancedInput();
};
