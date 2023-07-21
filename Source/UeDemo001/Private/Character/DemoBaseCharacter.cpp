// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DemoBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Missile/DemoBaseMissle.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/DamageTipWidget.h"
#include "kismet/KismetMathLibrary.h"

// Sets default values
ADemoBaseCharacter::ADemoBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//默认移动倍率，
	bIsRunning = false;
	bIsDie = false;

	//调整骨骼网格体方向及位置
	GetMesh()->SetRelativeRotation(DefaultRotateForSkm);
	GetMesh()->SetRelativeLocation(FVector(0,0,0 - GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	//设置固定视角
	bUseControllerRotationYaw = false;
	//设置面向运动
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	//创建武器节点
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"Weapon");
}

void ADemoBaseCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void ADemoBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(RecoverMpTimerHandle,this,&ADemoBaseCharacter::AutoRecoverMp,CharacterInfo.State.MpAutoRecoverRate,true);

	FOnTimelineFloatStatic OnDashTimeLineTick;
	FOnTimelineEventStatic OnDashTimeLineFinished;

	OnDashTimeLineTick.BindUFunction(this,TEXT("OnDashTick"));
	OnDashTimeLineFinished.BindUFunction(this,TEXT("OnDashFinished"));

	DashTimeLine.AddInterpFloat(DashCurve,OnDashTimeLineTick);
	DashTimeLine.SetTimelineFinishedFunc(OnDashTimeLineFinished);
	DashTimeLine.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
}

// Called every frame
void ADemoBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DashTimeLine.TickTimeline(DeltaTime);
}

void ADemoBaseCharacter::InitCharacterInfo()
{
	this->Weapon->SetVisibility(CharacterInfo.bFarAttack);
	this->SetActorRelativeScale3D(FVector(CharacterInfo.ScaleRate));
	SetCharacterMaxWalkSpeed(CharacterInfo.State.WalkSpeed);
	if(CharacterInfo.Skin)
	{
		this->GetMesh()->SetMaterial(0,CharacterInfo.Skin);	
	}
}

float ADemoBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                     AActor* DamageCauser)
{
	
	ADemoBaseCharacter* DamageCauserCharacter = Cast<ADemoBaseCharacter>(DamageCauser);
	if(nullptr == DamageCauserCharacter)
	{
		// UE_LOG(LogTemp,Warning,TEXT("未获取到伤害来源。。。。"));
		return 0.f;
	}

	//被击中后短暂冲刺
	TriggerTimeDash(0,0);

	//设置被击状态
	bIsHit = true;

	float Damage = 0.f;
	//计算伤害
	if(!bIsLockHp)
	{
		// UE_LOG(LogTemp,Warning,TEXT("%s==被攻击----"),*FName(this->GetName()).ToString());
		Damage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		this->CharacterInfo.State.CurHp  = CharacterInfo.State.CurHp - Damage <= 0 ? 0 : CharacterInfo.State.CurHp - Damage;
	}
	
	//死亡判定
	if(CharacterInfo.State.CurHp <= 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s==已死亡----"),*FName(this->GetName()).ToString());
		//设定死亡
		this->bIsDie = true;

		//受到伤害停止移动
		GetMovementComponent()->StopActiveMovement();

		//清除奔跑状态
		this->bIsRunning = false;
		//清除普通攻击状态
		this->bAttacking = false;
		//清除持续攻击状态
		this->bSustainedAttacking = false;
		//清除被击状态
		this->bIsHit = false;
		//设置死亡后不再生成重叠事件
		GetCapsuleComponent()->SetGenerateOverlapEvents(false);

		// UE_LOG(LogTemp,Warning,TEXT("开始获取伤害来源。。。。"));
		// UE_LOG(LogTemp,Warning,TEXT("开始计算%s经验值。。。。"),*FName(DamageCauserCharacter->GetName()).ToString());
		DamageCauserCharacter->CalculateExp(this->CharacterInfo.DieExp);
		
		//设置延迟销毁
		DelayDestroy();
	}else
	{
		//播放被攻击动画 
		PlayAnimMontage(HitAnimMontage,1.f);

		//显示伤害
		UDamageTipWidget* TipWidget = CreateWidget<UDamageTipWidget>(GetWorld(),DamageTipWidget);
		
		TipWidget->DamageValue = Damage;
		// UE_LOG(LogTemp,Warning,TEXT("造成了%d点伤害"),TipWidget->DamageValue);
		TipWidget->AddToViewport(0);
		FVector2D ScreenPosition ;
		UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(),GetActorLocation(),ScreenPosition);
		ScreenPosition.X += UKismetMathLibrary::RandomFloatInRange(-50,50.f);
		ScreenPosition.Y += UKismetMathLibrary::RandomFloatInRange(-25,25.f);
		TipWidget->SetPositionInViewport(ScreenPosition);	
	}
	return Damage;
}

void ADemoBaseCharacter::TriggerTimeDash(const float DurationTime, const float DashRate)
{
	if(DashCurve)
	{
		DashTimeLine.Play();
	}
}

void ADemoBaseCharacter::OnDashTick()
{
	float DushRate = DashCurve->GetFloatValue(DashTimeLine.GetPlaybackPosition());
	// UE_LOG(LogTemp,Warning,TEXT("获取到冲刺的倍率：%f"),DushRate);
	SetCharacterMaxWalkSpeed(CharacterInfo.State.WalkSpeed * DushRate);
}

void ADemoBaseCharacter::OnDashFinished()
{
	// UE_LOG(LogTemp,Warning,TEXT("加速冲刺完成。。。"));
}

void ADemoBaseCharacter::ExecuteDelayDestroy()
{
	GetWorldTimerManager().ClearTimer(DelayDestroyTimerHandle);
	GetWorldTimerManager().ClearTimer(RecoverMpTimerHandle);
	this->Destroy();
}

void ADemoBaseCharacter::RotateBeforeAttack()
{
	const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetAttackPointByMouse());
	SetActorRotation(FRotator(0,Rotator.Yaw,0));
}

void ADemoBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADemoBaseCharacter::CalculateExp(const int32 InExp)
{
	// UE_LOG(LogTemp,Warning,TEXT("%s本次获取经验值：%d"),*FName(this->GetName()).ToString(),InExp);
	// UE_LOG(LogTemp,Warning,TEXT("%s当前经验值：%d,最大经验值：%d"),*FName(this->GetName()).ToString(),CharacterInfo.CurExp,CharacterInfo.MaxExp);
	if(CharacterInfo.CurExp + InExp < CharacterInfo.MaxExp)
	{
		this->CharacterInfo.CurExp += InExp;
		// UE_LOG(LogTemp,Warning,TEXT("%s当前经验值：%d"),*FName(this->GetName()).ToString(),CharacterInfo.CurExp);
	}
	else
	{
		//升级
		LevelUp(CharacterInfo.CurExp + InExp - CharacterInfo.MaxExp);
	}
}

int32 ADemoBaseCharacter::LevelUp(const int32 LastLevelOverExp)
{
	// UE_LOG(LogTemp,Warning,TEXT("%s当前经验值已满，开始升级，多余经验：%d"),*FName(this->GetName()).ToString(),LastLevelOverExp);
	//等级+1
	this->CharacterInfo.Level ++;

	//计算下级经验最大值
	this->CharacterInfo.MaxExp  =  CharacterInfo.MaxExp * 1.85;

	//设置当前经验
	this->CharacterInfo.CurExp = LastLevelOverExp;

	//状态恢复
	this->CharacterInfo.State.CurHp = CharacterInfo.State.MaxHp;
	this->CharacterInfo.State.CurMp = CharacterInfo.State.MaxMp;
	return  this->CharacterInfo.Level;
}

void ADemoBaseCharacter::SetCharacterMaxWalkSpeed(float MaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

FCharacterInfo ADemoBaseCharacter::GetCharacterInfo()
{
	return this->CharacterInfo;
}

void ADemoBaseCharacter::AddState(const FCharacterState& InState)
{
	this->CharacterInfo.State += InState;
}

void ADemoBaseCharacter::AttackEndNotify()
{
	bAttacking = false;
}

void ADemoBaseCharacter::HitEndNotify()
{
	bIsHit = false;
}

void ADemoBaseCharacter::AttackFireBall()
{
	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetLocation(SpawnTransform.GetLocation() +  GetActorForwardVector() * 100);
	ADemoBaseMissle* NewMissile = Cast<ADemoBaseMissle>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(
			this,CharacterInfo.MissileClass,SpawnTransform,ESpawnActorCollisionHandlingMethod::AlwaysSpawn,this));
	UGameplayStatics::FinishSpawningActor(NewMissile,SpawnTransform);
}

void ADemoBaseCharacter::CommAttack()
{
	// UE_LOG(LogTemp,Warning,TEXT("ADemoBaseCharacter CommAttack 001"));
	if(!bAttacking && !bSustainedAttacking)	{
		// UE_LOG(LogTemp,Warning,TEXT("ADemoBaseCharacter CommAttack 002"));
		bAttacking = true;
		// this->RotateBeforeAttack();
		// UE_LOG(LogTemp,Warning,TEXT("ADemoBaseCharacter CommAttack 003"));
		PlayAnimMontage(CharacterInfo.AttackAnimMontage,CharacterInfo.AttackAnimMontageRate);
	}
}

void ADemoBaseCharacter::DelayDestroy()
{
	GetWorldTimerManager().SetTimer(DelayDestroyTimerHandle,this,&ADemoBaseCharacter::ExecuteDelayDestroy,CharacterInfo.DestroyDelay,false);
}

void ADemoBaseCharacter::MagicAttack()
{
	if(!GetMesh()->GetAnimInstance()->Montage_IsPlaying(MagicAttackAnimMontage))
	{
		if(CharacterInfo.State.CurMp <= 1)
		{
			return;
		}
		bSustainedAttacking = true;
		CharacterInfo.State.CurMp -= 1;
		PlayAnimMontage(MagicAttackAnimMontage,0.8f);
		this->CreateMagicFireBall(1,GetAttackPointByMouse());
	}
}

FVector ADemoBaseCharacter::GetAttackPointByMouse() const
{
	FHitResult HitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1,true,HitResult);
	return HitResult.Location;
}

void ADemoBaseCharacter::CreateMagicFireBall(const int32 BallCount, const FVector& TargetLocation)
{
	for (int i = 0; i < BallCount; ++i)
	{
		FVector StartLocation = TargetLocation + FVector(0 + UKismetMathLibrary::RandomFloatInRange(0.f,300.f),
			800 + UKismetMathLibrary::RandomFloatInRange(0.f,300.f),800 +UKismetMathLibrary::RandomFloatInRange(0.f,100.f));
		FVector RandomTargetLocation = TargetLocation + FVector(UKismetMathLibrary::RandomFloatInRange(0.f,100.f),
			UKismetMathLibrary::RandomFloatInRange(0.f,100.f),0);
		const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(StartLocation,RandomTargetLocation);
		ADemoBaseMissle* Missile = GetWorld()->SpawnActor<ADemoBaseMissle>(CharacterInfo.MissileClass,StartLocation ,Rotator);
		Missile->SetOwner(this);
	}
}

void ADemoBaseCharacter::AutoRecoverMp()
{
	if(CharacterInfo.State.CurMp <= CharacterInfo.State.MaxMp - CharacterInfo.State.MpAutoRecoverPoint)
	{
		this->CharacterInfo.State.CurMp += CharacterInfo.State.MpAutoRecoverPoint;	
	}
}

