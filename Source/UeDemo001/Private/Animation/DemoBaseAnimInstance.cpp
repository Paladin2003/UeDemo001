// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DemoBaseAnimInstance.h"
#include "GameFramework/Character.h"

void UDemoBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (const ACharacter* Character = PlayerController->GetCharacter())
		{
			Velocity = Character->GetVelocity().Length();
		}
	}
}
