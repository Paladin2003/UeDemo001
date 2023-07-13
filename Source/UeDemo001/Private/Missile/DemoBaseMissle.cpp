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
	this->SetLifeSpan(DestroyDelayTime);
}

void ADemoBaseMissle::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bOverlapped)
	{
		bOverlapped = true;
		if (ADemoBaseCharacter* DemoBaseCharacter = Cast<ADemoBaseCharacter>(Other))
		{
			//生成伤害
			UGameplayStatics::ApplyDamage(DemoBaseCharacter,Damage,DemoBaseCharacter->GetController(),this,nullptr);

			//创建爆炸特效
			UGameplayStatics::SpawnEmitterAtLocation(this,BoomParticle,this->GetActorLocation());

			this->Destroy();
		}
	}
}

// Called every frame
void ADemoBaseMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADemoBaseMissle::Destroyed()
{
	Super::Destroyed();
}

