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

// Called when the game starts or when spawned
void ADemoBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetCharacterMaxWalkSpeed(500.f);
}

// Called every frame
void ADemoBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ADemoBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//设置被击状态
	bIsHit = true;

	//受到伤害停止移动
	GetMovementComponent()->StopActiveMovement();
	
	//计算伤害
	UE_LOG(LogTemp,Warning,TEXT("%s==被攻击----"),*FName(this->GetName()).ToString());
	const float Damage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	this->CurHp  = CurHp - Damage <= 0 ? 0 : CurHp - Damage;

	//死亡判定
	if(CurHp <= 0)
	{
		//设定死亡
		this->bIsDie = true;
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
		//设置延迟销毁
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ADemoBaseCharacter::DelayDestroyed,DestroyDelay,false);
	}else
	{
		//播放被攻击动画 
		PlayAnimMontage(HitAnimMontage,1.f);

		//显示伤害
		UDamageTipWidget* TipWidget = CreateWidget<UDamageTipWidget>(GetWorld(),DamageTipWidget);
		TipWidget->DamageValue = Damage;
		TipWidget->AddToViewport(0);
		FVector2D ScreenPosition ;
		UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(),GetActorLocation(),ScreenPosition);
		ScreenPosition.X += UKismetMathLibrary::RandomFloatInRange(0,50.f);
		ScreenPosition.Y += UKismetMathLibrary::RandomFloatInRange(0,50.f);
		TipWidget->SetPositionInViewport(ScreenPosition);	
	}
	return Damage;
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

void ADemoBaseCharacter::SetCharacterMaxWalkSpeed(float MaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
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
	GetWorld()->SpawnActor<ADemoBaseMissle>(MissileClass,GetActorLocation() + GetActorForwardVector() * 100 ,GetActorRotation());
}

void ADemoBaseCharacter::CommAttack()
{
	if(!bAttacking && !bSustainedAttacking)	{
		bAttacking = true;
		this->RotateBeforeAttack();
		PlayAnimMontage(AttackAnimMontage,1.25f);
	}
}

void ADemoBaseCharacter::MagicAttack()
{
	bSustainedAttacking = true;
	if(!GetMesh()->GetAnimInstance()->Montage_IsPlaying(MagicAttackAnimMontage))
	{
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

void ADemoBaseCharacter::CreateMagicFireBall(const int32 BallCount, const FVector& TargetLocation) const
{
	for (int i = 0; i < BallCount; ++i)
	{
		FVector StartLocation = TargetLocation + FVector(0 + UKismetMathLibrary::RandomFloatInRange(0.f,300.f),
			800 + UKismetMathLibrary::RandomFloatInRange(0.f,300.f),800 +UKismetMathLibrary::RandomFloatInRange(0.f,100.f));
		FVector RandomTargetLocation = TargetLocation + FVector(UKismetMathLibrary::RandomFloatInRange(0.f,100.f),
			UKismetMathLibrary::RandomFloatInRange(0.f,100.f),0);
		const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(StartLocation,RandomTargetLocation);
		ADemoBaseMissle* Missile = GetWorld()->SpawnActor<ADemoBaseMissle>(MissileClass,StartLocation ,Rotator); 
	}
}

void ADemoBaseCharacter::DelayDestroyed()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	this->Destroy();
}

