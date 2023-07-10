// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DemoBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Missile/DemoBaseMissle.h"

// Sets default values
ADemoBaseCharacter::ADemoBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//默认移动倍率，
	bIsRunning = false;

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

void ADemoBaseCharacter::AttackFireBall()
{
	UE_LOG(LogTemp,Warning,TEXT("====普通攻击发射火球------"));
	ADemoBaseMissle* DemoBaseMissle = GetWorld()->SpawnActor<ADemoBaseMissle>(MissileClass,GetActorLocation() + GetActorForwardVector() * 100 ,GetActorRotation());
	DemoBaseMissle->SetLifeSpan(DemoBaseMissle -> DesdroyDelayTime);
}

void ADemoBaseCharacter::CommAttack()
{
	
}

