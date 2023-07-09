// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DemoDefaultGameMode.h"

#include "Character/Player/DemoDefaultPlayer.h"
#include "Game/DemoDefaultPlayerController.h"

ADemoDefaultGameMode::ADemoDefaultGameMode()
{
	DefaultPawnClass = ADemoDefaultPlayer::StaticClass();
	PlayerControllerClass = ADemoDefaultPlayerController::StaticClass();
}
