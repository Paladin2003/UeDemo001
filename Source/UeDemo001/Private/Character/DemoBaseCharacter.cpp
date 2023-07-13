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
	this->CurHp -= Damage;
	UE_LOG(LogTemp,Warning,TEXT("敌方【%s】受到%f点伤害,当前血量：%d/%d"),*FName(this->GetName()).ToString(),Damage,CurHp,MaxHp);

	//受到伤害停止移动
	GetMovementComponent()->StopActiveMovement();
	
	if(CurHp <= 0)
	{
		this->bIsDie = true;
		this->bIsRunning = false;
	}else
	{
		bIsHit = true;
		UE_LOG(LogTemp,Warning,TEXT("%s 播放受攻击动画。%s。"),*FName(this->GetName()).ToString(),*FName(HitAnimMontage->GetName()).ToString());

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
	UE_LOG(LogTemp,Warning,TEXT("%s 的 当前被攻击状态是：%d"),*FName(this->GetName()).ToString(),bIsHit);
}

void ADemoBaseCharacter::AttackFireBall()
{
	UE_LOG(LogTemp,Warning,TEXT("====普通攻击发射火球------"));
	ADemoBaseMissle* DemoBaseMissle = GetWorld()->SpawnActor<ADemoBaseMissle>(MissileClass,GetActorLocation() + GetActorForwardVector() * 100 ,GetActorRotation());
	DemoBaseMissle->SetLifeSpan(DemoBaseMissle -> DestroyDelayTime);
}

void ADemoBaseCharacter::CommAttack()
{
	if(!bAttacking)	{
		bAttacking = true;
		bLockRotate = true;
		
		FHitResult HitResult;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1,true,HitResult);
		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),HitResult.Location);
		SetActorRotation(FRotator(0,Rotator.Yaw,0));
		PlayAnimMontage(AttackAnimMontage,1.25f);
		
	}
}

