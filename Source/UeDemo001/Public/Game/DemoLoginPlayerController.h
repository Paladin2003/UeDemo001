// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widget/DemoStartMenuWidget.h"
#include "DemoLoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UEDEMO001_API ADemoLoginPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADemoLoginPlayerController();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UDemoStartMenuWidget> StartMenuWidgetClass;

	virtual void BeginPlay() override;
};
