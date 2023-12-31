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
		//排除发射物创建者
		if (Other->GetClass() == this->GetOwner()->GetClass())
		{
			return;
		}
		/*UE_LOG(LogTemp,Warning,TEXT("重叠对象%s类型：%s====；自动发动者对象类型：%s"),
			*FName(Other->GetName()).ToString(),
			*FName(Other->GetClass()->GetName()).ToString(),
			*FName(this->GetOwner()->GetClass()->GetName()).ToString())*/
		// UE_LOG(LogTemp,Warning,TEXT("子弹%s已命中。。。"),*FName(this->GetName()).ToString());
		bOverlapped = true;
		
		if (ADemoBaseCharacter* DemoBaseCharacter = Cast<ADemoBaseCharacter>(Other); DemoBaseCharacter && !
			DemoBaseCharacter->bIsDie)
		{
			//生成伤害
			//UE_LOG(LogTemp,Warning,TEXT("子弹%s对%s造成直接伤害"),*this->GetName(),*Other->GetName());
			UGameplayStatics::ApplyDamage(DemoBaseCharacter, Damage,
				DemoBaseCharacter->GetController(),
				this->GetOwner(), nullptr);

		}
		//创建爆炸特效
		UGameplayStatics::SpawnEmitterAtLocation(this, BoomParticle, this->GetActorLocation());

		TArray<FHitResult>* OutHits = new TArray<FHitResult>{};
		//生成爆炸范围检测
		const bool bHasBoomDamaged = UKismetSystemLibrary::SphereTraceMultiForObjects(this,
									FVector(this->GetActorLocation().X,this->GetActorLocation().Y,0),
									FVector(this->GetActorLocation().X,this->GetActorLocation().Y,0),
									500.f, {EObjectTypeQuery::ObjectTypeQuery3}, false, {this->GetOwner()},
									EDrawDebugTrace::None, *OutHits, true,FLinearColor::Red,
									FLinearColor::Green, 5.f);
		// 生成爆炸伤害
		if (bHasBoomDamaged && !OutHits->IsEmpty()) 
		{
			 //UE_LOG(LogTemp,Warning,TEXT("有%d名敌人被子弹%s产生的爆炸击中"),OutHits->Num(),*FName(this->GetName()).ToString());
			for(auto i = OutHits->begin();i != OutHits->end();++i)
			{
				const FHitResult HitResult = *i;
				// UE_LOG(LogTemp,Warning,TEXT("循环当前被爆炸击中的敌人：%s"),*FName(HitResult.GetActor()->GetName()).ToString());
				if (ADemoBaseCharacter* BaseCharacter = Cast<ADemoBaseCharacter>(HitResult.GetActor()) ;
					BaseCharacter && ! BaseCharacter->bIsDie)
				{
					UGameplayStatics::ApplyDamage(BaseCharacter,
						UKismetMathLibrary::RandomFloatInRange(1.f,Damage),
						BaseCharacter->GetController(), this->GetOwner(), nullptr);
					MissileEffect(BaseCharacter);
				}
			}
		}
		// this->Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// this->Mesh->SetVisibility(false);
		// this->Particle->SetVisibility(false);
		
		// this->Destroy();
	}
}

void ADemoBaseMissle::MissileEffect(ADemoBaseCharacter* InCharacter)
{
	UE_LOG(LogTemp,Warning,TEXT("触发特殊效果。。。"));
	DamagedCharacter = InCharacter;
	this->SetLifeSpan(this->GetLifeSpan() >= DebuffTime ? this->GetLifeSpan() : DebuffTime );
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&ADemoBaseMissle::EffectInvoke,1.f,true);
}

void ADemoBaseMissle::EffectInvoke()
{
	if(DamagedCharacter)
	{
		UGameplayStatics::ApplyDamage(DamagedCharacter, DebuffDamage,
				DamagedCharacter->GetController(),
				this->GetOwner(),nullptr);
	}
}

// Called every frame
void ADemoBaseMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADemoBaseMissle::Destroyed()
{
	UE_LOG(LogTemp,Warning,TEXT("开始执行销毁。。"));
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	Super::Destroyed();
}
