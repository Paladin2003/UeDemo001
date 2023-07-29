// Fill out your copyright notice in the Description page of Project Settings.


#include "Curves/DemoCurveFloat.h"

void UDemoCurveFloat::SetCurveKey(const float Key, const float Value)
{
	FloatCurve.AddKey(Key,Value);
}
