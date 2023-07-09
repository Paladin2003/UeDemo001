// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DemoBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADemoBaseCharacter::ADemoBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//默认移动倍率，
	bIsRunning = false;
	MovementRate = 0.5f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;

	//调整骨骼网格体方向及位置
	GetMesh()->SetRelativeRotation(DefaultRotateForSkm);
	GetMesh()->SetRelativeLocation(FVector(0,0,0 - GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

// Called when the game starts or when spawned
void ADemoBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void ADemoBaseCharacter::CharacterRotate(FVector Vector)
{
	SetActorRotation(UKismetMathLibrary::MakeRotFromX(Vector));
}
