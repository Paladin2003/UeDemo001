// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "DemoCurveFloat.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UEDEMO001_API UDemoCurveFloat : public UCurveFloat
{
	GENERATED_BODY()

public:

	void SetCurveKey(const float Key,const float Value );
};
