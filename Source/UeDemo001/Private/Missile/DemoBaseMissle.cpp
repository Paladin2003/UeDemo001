// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile/DemoBaseMissle.h"
#include "Character/Enemy/DemoDefaultEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "kismet/KismetSystemLibrary.h"

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
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADemoBaseMissle::BeginOverlap);

	//网格体组件
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);

	//添加发射移动组件
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movenent"));
	Movement->MaxSpeed = 3000.f;
	Movement->InitialSpeed = 2000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bRotationRemainsVertical = true;
	Movement->ProjectileGravityScale = 0;

	//特效组件
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Partical"));
	Particle->AttachToComponent(Sphere, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ADemoBaseMissle::BeginPlay()
{
	Super::BeginPlay();
	this->SetLifeSpan(DestroyDelayTime);
}

void ADemoBaseMissle::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bOverlapped)
	{
		// UE_LOG(LogTemp,Warning,TEXT("子弹%s已命中。。。"),*FName(this->GetName()).ToString());
		bOverlapped = true;
		
		if (ADemoBaseCharacter* DemoBaseCharacter = Cast<ADemoBaseCharacter>(Other); DemoBaseCharacter && !
			DemoBaseCharacter->bIsDie)
		{
			//生成伤害
			UGameplayStatics::ApplyDamage(DemoBaseCharacter, Damage, DemoBaseCharacter->GetController(), this, nullptr);
		}

		//创建爆炸特效
		UGameplayStatics::SpawnEmitterAtLocation(this, BoomParticle, this->GetActorLocation());

		TArray<FHitResult>* OutHits = new TArray<FHitResult>{};
		//生成爆炸范围检测
		const bool bHasBoomDamaged = UKismetSystemLibrary::SphereTraceMultiForObjects(this,
									FVector(this->GetActorLocation().X,this->GetActorLocation().Y,0),
									FVector(this->GetActorLocation().X,this->GetActorLocation().Y,0),
									500.f, {EObjectTypeQuery::ObjectTypeQuery3}, false, {},
									EDrawDebugTrace::Persistent, *OutHits, true,FLinearColor::Red,
									FLinearColor::Green, 5.f);
		// 生成爆炸伤害
		if (bHasBoomDamaged && !OutHits->IsEmpty()) 
		{
			// UE_LOG(LogTemp,Warning,TEXT("有%d名敌人被子弹%s产生的爆炸击中"),OutHits->Num(),*FName(this->GetName()).ToString());
			for(auto i = OutHits->begin();i != OutHits->end();++i)
			{
				const FHitResult HitResult = *i;
				// UE_LOG(LogTemp,Warning,TEXT("循环当前被爆炸击中的敌人：%s"),*FName(HitResult.GetActor()->GetName()).ToString());
				if (ADemoBaseCharacter* BaseCharacter = Cast<ADemoBaseCharacter>(HitResult.GetActor()))
				{
					UGameplayStatics::ApplyDamage(BaseCharacter,
						UKismetMathLibrary::RandomFloatInRange(1.f,Damage),
						BaseCharacter->GetController(), this, nullptr);
				}
			}
		}
		this->Destroy();
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
