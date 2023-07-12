// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile/DemoBaseMissle.h"
#include "Character/Enemy/DemoDefaultEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADemoBaseMissle::ADemoBaseMissle()
{
	PrimaryActorTick.bCanEverTick = true;

	//延迟销毁的时间
	DestroyDelayTime = 3;

	//创建根节点
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Sphere->OnComponentBeginOverlap.RemoveDynamic(this, &ADemoBaseMissle::BeginOverlap);
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&ADemoBaseMissle::BeginOverlap);

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

void ADemoBaseMissle::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("触发重叠事件。。。。"));
	
	if (ADemoDefaultEnemy* DemoDefaultEnemy = Cast<ADemoDefaultEnemy>(Other))
	{
		UE_LOG(LogTemp,Warning,TEXT("击中目标：%s"),*FName(DemoDefaultEnemy->GetName()).ToString());

		UGameplayStatics::ApplyDamage(DemoDefaultEnemy,Damage,DemoDefaultEnemy->GetController(),this,nullptr);
	}

	
}

// Called every frame
void ADemoBaseMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

