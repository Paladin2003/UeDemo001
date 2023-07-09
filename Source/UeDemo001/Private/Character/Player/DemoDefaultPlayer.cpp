// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/DemoDefaultPlayer.h"
#include "EnhancedInputComponent.h"
#include "Engine/HitResult.h"

ADemoDefaultPlayer::ADemoDefaultPlayer()
{
	//创建弹簧臂组件
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	CameraArm->TargetArmLength = 800.f;
	CameraArm->SetRelativeRotation(FRotator(-35,0,0));
	CameraArm->bDoCollisionTest = false;
	CameraArm->bInheritPitch = false;
	CameraArm->bInheritYaw = false;
	CameraArm->bInheritRoll = false;

	//创建摄像机组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CameraArm,FAttachmentTransformRules::KeepRelativeTransform);
	
}

void ADemoDefaultPlayer::BeginPlay()
{
	Super::BeginPlay();
	InitEnhancedInput();
}

void ADemoDefaultPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
			if(MovementInputAction)
			{
				EnhancedInputComponent->BindAction(MovementInputAction,ETriggerEvent::Triggered,this,&ADemoDefaultPlayer::MovementForEnhancedInput);
			}
			if(LookUpInputAction)
			{
				EnhancedInputComponent->BindAction(LookUpInputAction,ETriggerEvent::Triggered,this,&ADemoDefaultPlayer::LookUpForEnhancedInput);
			}
			if(RunningInputAction)
			{
				EnhancedInputComponent->BindAction(RunningInputAction,ETriggerEvent::Started,this,&ADemoDefaultPlayer::RunningForEnhancedInput);
				EnhancedInputComponent->BindAction(RunningInputAction,ETriggerEvent::Completed,this,&ADemoDefaultPlayer::RunningForEnhancedInput);
			}
		}
	}
}

void ADemoDefaultPlayer::MovementForEnhancedInput(const FInputActionValue& InputActionValue)
{
	const FVector2d MovementValue = InputActionValue.Get<FVector2d>();
	AddMovementInput(FVector(1,0,0),MovementRate * MovementValue.X);
	AddMovementInput(FVector(0,1,0),MovementRate * MovementValue.Y);
}

void ADemoDefaultPlayer::LookUpForEnhancedInput(const FInputActionValue& InputActionValue)
{
	const FVector2d LookUpValue = InputActionValue.Get<FVector2d>();
}

void ADemoDefaultPlayer::RunningForEnhancedInput(const FInputActionValue& InputActionValue)
{
	bIsRunning = InputActionValue.Get<bool>();
	MovementRate = bIsRunning ? 1.0f : 0.5f;
}
