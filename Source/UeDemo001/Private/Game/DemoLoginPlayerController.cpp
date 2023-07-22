// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DemoLoginPlayerController.h"

#include "Blueprint/UserWidget.h"

void ADemoLoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(StartMenuWidgetClass)
	{
		UUserWidget* Widget =  CreateWidget(GetWorld(),StartMenuWidgetClass);
		Widget->AddToViewport(0);
	}
}
