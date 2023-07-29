// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile/DemoMissleTornado.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ADemoMissleTornado::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TornadoTimerHandle,this,&ADemoMissleTornado::TornadoInvoke,0.02f,true);
}

void ADemoMissleTornado::TornadoInvoke()
{
	UE_LOG(LogTemp,Warning,TEXT("TornadoInvoke....."));
	TArray<FHitResult>* OutHits = new TArray<FHitResult>{};
	//生成爆炸范围检测
	const bool bHasBoomDamaged = UKismetSystemLibrary::SphereTraceMultiForObjects(this,
								FVector(this->GetActorLocation().X,this->GetActorLocation().Y,0),
								FVector(this->GetActorLocation().X,this->GetActorLocation().Y,0),
								800.f, {EObjectTypeQuery::ObjectTypeQuery3}, false, {this->GetOwner()},
								EDrawDebugTrace::None, *OutHits, true,FLinearColor::Red,
								FLinearColor::Green, 1.f);

	if (bHasBoomDamaged && !OutHits->IsEmpty()) 
	{
		for(auto i = OutHits->begin();i != OutHits->end();++i)
		{
			const FHitResult HitResult = *i;
			if (ADemoBaseCharacter* BaseCharacter = Cast<ADemoBaseCharacter>(HitResult.GetActor()) ;
				BaseCharacter && ! BaseCharacter->bIsDie)
			{
				FRotator LookRotator = UKismetMathLibrary::FindLookAtRotation(BaseCharacter->GetActorLocation(),this->GetActorLocation());
				BaseCharacter->SetActorLocation(BaseCharacter->GetActorLocation()+UKismetMathLibrary::Conv_RotatorToVector(LookRotator)*10);
				
				// BaseCharacter->AddMovementInput(UKismetMathLibrary::Conv_RotatorToVector(LookRotator),1000,true);
			}
		}
	}
}

void ADemoMissleTornado::MissileEffect(ADemoBaseCharacter* InCharacter)
{
	// Super::MissileEffect(InCharacter);
}

void ADemoMissleTornado::EffectInvoke()
{
		// Super::EffectInvoke();
}


