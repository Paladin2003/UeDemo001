// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile/DemoBaseMissle.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADemoBaseMissle::ADemoBaseMissle()
{
	PrimaryActorTick.bCanEverTick = true;

	//延迟销毁的时间
	DesdroyDelayTime = 3;

	//创建根节点
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	//网格体组件
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Sphere,FAttachmentTransformRules::KeepRelativeTransform);

	//添加发射移动组件
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movenent"));
	Movement->MaxSpeed = 3000.f;
	Movement->InitialSpeed = 2000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bRotationRemainsVertical = true;
	Movement->ProjectileGravityScale = 0;

	//特效组件
	Partical = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Partical"));
	Partical->AttachToComponent(Sphere,FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ADemoBaseMissle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADemoBaseMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

