// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Character/DemoBaseCharacter.h"
#include "Struct/PropInfo.h"
#include "DemoBaseProp.generated.h"

UCLASS()
class UEDEMO001_API ADemoBaseProp : public AActor
{
	GENERATED_BODY()
	
public:	
	ADemoBaseProp();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UNiagaraComponent* Niagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generate")
	FString PropName = "Prop001";
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* PropData;
	
	FPropInfo PropInfo;

	/**
	* @brief 执行道具效果
	*/
	virtual void DoPropEffect(ADemoBaseCharacter* Character);

	//====================
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginComponentOverlapped(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	virtual void Tick(float DeltaTime) override;

private:

	void InitPropInfo();
};
