// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CaptureScreenHelper.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCaptureScreenDelegate,const FString&,ImagePath);

UENUM(BlueprintType)
enum class EImageFormatType :uint8
{
	PNG,
	JPEG
};

UCLASS()
class UEDEMO001_API UCaptureScreenHelper : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(WorldContext = "WorldContextObject"))
	static UCaptureScreenHelper* CaptureScreen(UObject* WorldContextObject, const FString& InImageName,
		EImageFormatType InFormat,int32 InWidth = 1920,int32 InHeight = 1080,int32 InQuality = 100);

	UPROPERTY(BlueprintAssignable)
	FCaptureScreenDelegate OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCaptureScreenDelegate OnFail;
	

	void ScreenshotCaptured( int32 Width, int32 Height, const TArray<FColor>& Colors);

	
	FString GetImageName();
	
	// static FDelegateHandle DelegateHandle;

	/*UFUNCTION(BlueprintCallable)
	static void CaptureScreenshot(const int32 InWidth, const int32 InHeight, const FString CaptureName);

	static void OnScreenshotCompleteToPng(const int32 InWidth, const int32 InHeight, const TArray<FColor>& InColor);

	static void OnScreenshotCompleteToJpg(int32 InWidth, int32 InHeight, const TArray<FColor>& InColor);*/

private:
	UPROPERTY()
	FString ImageName;

	UPROPERTY()
	EImageFormatType Format;

	UPROPERTY()
	int32 Quality;

	FDelegateHandle DelegateHandle;
};
