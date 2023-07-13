// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/DemoDefaultPlayer.h"
#include "EnhancedInputComponent.h"
#include "Engine/HitResult.h"

ADemoDefaultPlayer::ADemoDefaultPlayer()
{

	bAttacking = false;
	
	//创建弹簧臂组件
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	CameraArm->TargetArmLength = 2000.f;
	CameraArm->SetRelativeRotation(FRotator(-45,0,0));
	CameraArm->bDoCollisionTest = false;
	CameraArm->bInheritPitch = false;
	CameraArm->bInheritYaw = false;
	CameraArm->bInheritRoll = false;

	//创建摄像机组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(CameraArm,FAttachmentTransformRules::KeepRelativeTransform);
}

void ADemoDefaultPlayer::AttackFireBall()
{
	Super::AttackFireBall();
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

void ADemoDefaultPlayer::CommAttack()
{
	Super::CommAttack();
}

void ADemoDefaultPlayer::InitEnhancedInput()
{
	if (const APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MovementInputMappingContext,0);
		}
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(MovementInputAction,ETriggerEvent::Triggered,this,&ADemoDefaultPlayer::MovementForEnhancedInput);
			EnhancedInputComponent->BindAction(MovementInputAction,ETriggerEvent::Triggered,this,&ADemoDefaultPlayer::MovementForEnhancedInput);
			EnhancedInputComponent->BindAction(RunningInputAction,ETriggerEvent::Started,this,&ADemoDefaultPlayer::RunningForEnhancedInput);
			EnhancedInputComponent->BindAction(RunningInputAction,ETriggerEvent::Completed,this,&ADemoDefaultPlayer::RunningForEnhancedInput);

			EnhancedInputComponent->BindAction(AttackInputAction,ETriggerEvent::Started,this,&ADemoDefaultPlayer::AttackForEnhancedInput);
			EnhancedInputComponent->BindAction(MagicAttackInputAction,ETriggerEvent::Triggered,this,&ADemoDefaultPlayer::MagicAttackForEnhancedInput);
			EnhancedInputComponent->BindAction(MagicAttackInputAction,ETriggerEvent::Completed,this,&ADemoDefaultPlayer::EndMagicAttackForEnhancedInput);
			
		}
	}
}

void ADemoDefaultPlayer::MovementForEnhancedInput(const FInputActionValue& InputActionValue)
{
	const FVector2d MovementValue = InputActionValue.Get<FVector2d>();
	AddMovementInput(FVector(1,0,0) * MovementValue.X, 1);
	AddMovementInput(FVector(0,1,0) * MovementValue.Y,1);
}

void ADemoDefaultPlayer::RunningForEnhancedInput(const FInputActionValue& InputActionValue)
{
	bIsRunning = InputActionValue.Get<bool>();
	SetCharactorMaxWalkSpeed(bIsRunning ? 800.f : 500.f);
}

void ADemoDefaultPlayer::AttackForEnhancedInput(const FInputActionValue& InputActionValue)
{
	CommAttack();
}

void ADemoDefaultPlayer::MagicAttackForEnhancedInput(const FInputActionValue& InputActionValue)
{
	MagicAttack();
}

void ADemoDefaultPlayer::EndMagicAttackForEnhancedInput(const FInputActionValue& InputActionValue)
{
	bSustainedAttacking = false;
}
	
