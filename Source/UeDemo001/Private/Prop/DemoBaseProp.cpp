// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/DemoBaseProp.h"

#include "Character/Player/DemoDefaultPlayer.h"
#include "Components/SphereComponent.h"

// Sets default values
ADemoBaseProp::ADemoBaseProp()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->OnComponentBeginOverlap.RemoveDynamic(this, &ADemoBaseProp::OnBeginComponentOverlapped);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADemoBaseProp::OnBeginComponentOverlapped);
	Sphere->SetSphereRadius(80.f);
	
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->AttachToComponent(Sphere,FAttachmentTransformRules::KeepRelativeTransform);
}

void ADemoBaseProp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADemoBaseProp::DoPropEffect(ADemoBaseCharacter* Character)
{
	Character->AddState(GetPropState());
}

FCharacterState ADemoBaseProp::GetPropState()
{
	
	return FCharacterState(this->PropInfo.RecoverHp,this->PropInfo.RecoverMp);
}

void ADemoBaseProp::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (nullptr != PropData)
	{
		for (auto DataRow : PropData->GetRowMap())
		{
			FName& RowName = DataRow.Key;
			if (PropName == RowName.ToString())
			{
				this->PropInfo = *reinterpret_cast<FPropInfo*>(DataRow.Value);
				InitPropInfo();
				break;
			}
		}
	}
}

// Called every frame
void ADemoBaseProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADemoBaseProp::OnBeginComponentOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("道具重叠事件开始。。。。。"));
	if(ADemoDefaultPlayer* DefaultPlayer = Cast<ADemoDefaultPlayer>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("%s拾取了道具：%s") , *FName(DefaultPlayer->GetName()).ToString(),*this->GetName());
		DoPropEffect(DefaultPlayer);
		this->Destroy();
	}
}

void ADemoBaseProp::InitPropInfo()
{
	Niagara->SetAsset(PropInfo.NiagaraSystem);
}

