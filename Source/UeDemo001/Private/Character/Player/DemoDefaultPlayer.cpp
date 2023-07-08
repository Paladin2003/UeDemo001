// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/DemoDefaultPlayer.h"

#include "Components/CapsuleComponent.h"

ADemoDefaultPlayer::ADemoDefaultPlayer()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	CameraArm->TargetArmLength = 800.f;
	CameraArm->SetRelativeRotation(FRotator(-35,0,0));
	CameraArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CameraArm,FAttachmentTransformRules::KeepRelativeTransform);

	if (USkeletalMeshComponent* SkeletaMesh = GetComponentByClass<USkeletalMeshComponent>())
	{
		SkeletaMesh->SetRelativeRotation(FRotator(0,-90,0));
		if (const UCapsuleComponent* Capsule = CastChecked<UCapsuleComponent>(GetRootComponent()))
		{
			SkeletaMesh->SetRelativeLocation(FVector(0,0,0 - Capsule->GetScaledCapsuleHalfHeight()));	
		}
	}
}

void ADemoDefaultPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	InitEnhancedInput();
}

void ADemoDefaultPlayer::InitEnhancedInput()
{
	
}
