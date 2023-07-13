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
	SetCharactorMaxWalkSpeed(500.f);
}

// Called every frame
void ADemoBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ADemoBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float Damage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	this->CurHp  = CurHp - Damage <= 0 ? 0 : CurHp - Damage;

	//受到伤害停止移动
	GetMovementComponent()->StopActiveMovement();
	
	if(CurHp <= 0)
	{
		this->bIsDie = true;
		this->bIsRunning = false;
		GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ADemoBaseCharacter::DelayDestroyed,2.5f,false);
	}else
	{
		bIsHit = true;
		PlayAnimMontage(HitAnimMontage,1.f);
		
		UDamageTipWidget* TipWidget = CreateWidget<UDamageTipWidget>(GetWorld(),DamageTipWidget);
		TipWidget->DamageValue = Damage;
		TipWidget->AddToViewport(0);
		FVector2D ScreenPosition ;
		UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(),GetActorLocation(),ScreenPosition);
		TipWidget->SetPositionInViewport(ScreenPosition);	
	}
	return Damage;
}

FVector ADemoBaseCharacter::RotateBeforeAttack()
{
	FHitResult HitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1,true,HitResult);
	const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),HitResult.Location);
	SetActorRotation(FRotator(0,Rotator.Yaw,0));
	return HitResult.Location;
}

// Called to bind functionality to input
void ADemoBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADemoBaseCharacter::SetCharactorMaxWalkSpeed(float MaxWalkSpeed)
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
	FVector TargetLocation = RotateBeforeAttack();
	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(MagicAttackAnimMontage)) 
	{
		PlayAnimMontage(MagicAttackAnimMontage,0.35f);
		this->CreateMagicFireBall(5,TargetLocation);
	}
}

void ADemoBaseCharacter::CreateMagicFireBall(const int32 BallCount, const FVector& TargetLocation) const
{
	for (int i = 0; i < BallCount; ++i)
	{
		FVector StartLocation = TargetLocation + FVector(0 + UKismetMathLibrary::RandomFloatInRange(0.f,200.f),
			800 + UKismetMathLibrary::RandomFloatInRange(0.f,200.f),800 +UKismetMathLibrary::RandomFloatInRange(0.f,100.f));
		FVector RandomTargetLocation = TargetLocation + FVector(UKismetMathLibrary::RandomFloatInRange(0.f,200.f),
			UKismetMathLibrary::RandomFloatInRange(0.f,200.f),0);
		const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(StartLocation,RandomTargetLocation);
		GetWorld()->SpawnActor<ADemoBaseMissle>(MissileClass,StartLocation ,Rotator);
	}
}

void ADemoBaseCharacter::DelayDestroyed()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	this->Destroy();
}

