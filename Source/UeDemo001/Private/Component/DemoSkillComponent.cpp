// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DemoSkillComponent.h"

UDemoSkillComponent::UDemoSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDemoSkillComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDemoSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

