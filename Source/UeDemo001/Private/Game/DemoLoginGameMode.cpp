// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DemoLoginGameMode.h"

#include "Game/DemoLoginPlayerController.h"

ADemoLoginGameMode::ADemoLoginGameMode()
{
	PlayerControllerClass = ADemoLoginPlayerController::StaticClass();
}
