// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/DemoDefaultPlayer.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADemoDefaultPlayer::ADemoDefaultPlayer()
{
	//创建弹簧臂组件
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	CameraArm->TargetArmLength = 800.f;
	CameraArm->SetRelativeRotation(FRotator(-35,0,0));
	CameraArm->bDoCollisionTest = false;

	//创建摄像机组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CameraArm,FAttachmentTransformRules::KeepRelativeTransform);

	//调整骨骼网格体方向及位置
	if (USkeletalMeshComponent* SkeletaMesh = GetComponentByClass<USkeletalMeshComponent>())
	{
		SkeletaMesh->SetRelativeRotation(FRotator(0,-90,0));
		if (const UCapsuleComponent* Capsule = CastChecked<UCapsuleComponent>(GetRootComponent()))
		{
			SkeletaMesh->SetRelativeLocation(FVector(0,0,0 - Capsule->GetScaledCapsuleHalfHeight()));	
		}
	}

	//默认移动倍率，
	MovementRate = 5.f;
	// GetCharacterMovement()->Velocity
}

void ADemoDefaultPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	InitEnhancedInput();
}

void ADemoDefaultPlayer::Move()
{
	
}

void ADemoDefaultPlayer::InitEnhancedInput()
{
	if(nullptr == MovementInputMappingContext)
	{
		return;
	}
	if (APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MovementInputMappingContext,0);
		}
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(MovementInputAction,ETriggerEvent::Triggered,this,&ADemoDefaultPlayer::MovementForEnhancedInput);
		}
	}
}

void ADemoDefaultPlayer::MovementForEnhancedInput(const FInputActionValue& InputActionValue)
{
	const FVector2d MovementValue = InputActionValue.Get<FVector2d>();

	AddMovementInput(GetActorForwardVector() * MovementValue.X,MovementRate);
	AddMovementInput(GetActorRightVector() * MovementValue.Y,MovementRate);
}