// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DemoBaseAnimInstance.h"
#include "Character/DemoBaseCharacter.h"
#include "Character/Player/DemoDefaultPlayer.h"

UDemoBaseAnimInstance::UDemoBaseAnimInstance()
{
}

void UDemoBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ADemoBaseCharacter* OwnerCharacter  = Cast<ADemoBaseCharacter>(TryGetPawnOwner()))
	{
		bAttacking = OwnerCharacter->bAttacking;
		bDie = OwnerCharacter->bIsDie;
		bHit = OwnerCharacter->bIsHit;
		UE_LOG(LogTemp,Warning,TEXT(""));
		Velocity = OwnerCharacter->GetVelocity().Length();
	} 
}
