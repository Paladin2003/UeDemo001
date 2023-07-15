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

	//创建后期盒子组件
	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcess->AttachToComponent(CameraArm,FAttachmentTransformRules::KeepRelativeTransform);
}

void ADemoDefaultPlayer::AttackFireBall()
{
	Super::AttackFireBall();
}

void ADemoDefaultPlayer::BeginPlay()
{
	Super::BeginPlay();
	InitEnhancedInput();

	if (FloatCurve)
	{
		FOnTimelineFloatStatic OnMagicAttackTickCallBack;
		FOnTimelineEventStatic OnMagicAttackEndCallBack;
		//绑定时间轴播放时每帧触发的事件
		OnMagicAttackTickCallBack.BindUFunction(this,TEXT("SustainedAttackPostBlendCallBack"));
		//绑定时间轴播放播放完成时触发的事件
		OnMagicAttackEndCallBack.BindUFunction(this,TEXT("SustainedAttackPostBlendFinishedCallBack"));

		//绑定时间轴的曲线
		TimeLine.AddInterpFloat(FloatCurve,OnMagicAttackTickCallBack);
		TimeLine.SetTimelineFinishedFunc(OnMagicAttackEndCallBack);
		TimeLine.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	}
}

void ADemoDefaultPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TimeLine.TickTimeline(DeltaSeconds);
}

void ADemoDefaultPlayer::CommAttack()
{
	Super::CommAttack();
}

void ADemoDefaultPlayer::SustainedAttackPostBlendCallBack()
{
	float FloatCurveVal= FloatCurve->GetFloatValue(TimeLine.GetPlaybackPosition());
	//float LerpRet = UKismetMathLibrary::Lerp(0.f,1.f,FloatCurveVal);
	PostProcess->BlendWeight = FloatCurveVal;
}

void ADemoDefaultPlayer::SustainedAttackPostBlendFinishedCallBack()
{
	
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
	if(!bAttacking)
	{
		const FVector2d MovementValue = InputActionValue.Get<FVector2d>();
		AddMovementInput(FVector(1,0,0) * MovementValue.X, 1);
		AddMovementInput(FVector(0,1,0) * MovementValue.Y,1);
	}
}

void ADemoDefaultPlayer::RunningForEnhancedInput(const FInputActionValue& InputActionValue)
{
	bIsRunning = InputActionValue.Get<bool>();
	SetCharacterMaxWalkSpeed(bIsRunning ? 800.f : 500.f);
}

void ADemoDefaultPlayer::AttackForEnhancedInput(const FInputActionValue& InputActionValue)
{
	CommAttack();

}

void ADemoDefaultPlayer::MagicAttackForEnhancedInput(const FInputActionValue& InputActionValue)
{
	MagicAttack();
	
	if(FloatCurve && !TimeLine.IsPlaying())
	{
		TimeLine.Play();
	}
}

void ADemoDefaultPlayer::EndMagicAttackForEnhancedInput(const FInputActionValue& InputActionValue)
{
	bSustainedAttacking = false;

	if(FloatCurve && !TimeLine.IsReversing())
	{
		TimeLine.Reverse();
	}
}
	
