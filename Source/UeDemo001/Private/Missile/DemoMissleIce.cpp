// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile/DemoMissleIce.h"

void ADemoMissleIce::MissileEffect(ADemoBaseCharacter* InCharacter)
{
	InCharacter->TriggerTimeDash(0,SlowDownRate);
}
