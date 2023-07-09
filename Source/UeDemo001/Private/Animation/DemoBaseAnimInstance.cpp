// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DemoBaseAnimInstance.h"
#include "Character/DemoBaseCharacter.h"

UDemoBaseAnimInstance::UDemoBaseAnimInstance()
{
}

void UDemoBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ACharacter* Character = PlayerController->GetCharacter())
		{
			if (ADemoBaseCharacter* DemoCharacter = CastChecked<ADemoBaseCharacter>(Character))
			{
				Velocity = DemoCharacter->GetVelocity().Length();
				bAttacking = DemoCharacter->bAttacking;
			}
		}
	}
}
