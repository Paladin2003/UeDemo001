// Fill out your copyright notice in the Description page of Project Settings.

#include "Library/CaptureScreenHelper.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"

// FDelegateHandle UCaptureScreenHelper::DelegateHandle = {};

UCaptureScreenHelper* UCaptureScreenHelper::CaptureScreen(UObject* WorldContextObject, const FString& InImageName,
                                                          EImageFormatType InFormat, int32 InWidth, int32 InHeight, int32 InQuality)
{
	UCaptureScreenHelper* CaptureScreenHelperInstance = NewObject<UCaptureScreenHelper>();

	CaptureScreenHelperInstance->Format = InFormat;
	CaptureScreenHelperInstance->Quality = InQuality;

	FString ImageTempName;
	if(InFormat == EImageFormatType::PNG)
	{
		ImageTempName = InImageName + TEXT(".png");
	}
	if(InFormat == EImageFormatType::JPEG)
	{
		ImageTempName = InImageName + TEXT(".jpg");
	}

	CaptureScreenHelperInstance->ImageName = FPaths::ProjectSavedDir() + TEXT("CaptureScreen/") + ImageTempName;

	CaptureScreenHelperInstance->DelegateHandle = UGameViewportClient::OnScreenshotCaptured().AddUObject(CaptureScreenHelperInstance,&UCaptureScreenHelper::ScreenshotCaptured);

	FString CmdStr = FString::Printf(TEXT("HighResShot %dx%d"),InWidth,InHeight);
	
	GEngine->GameViewport->Exec(WorldContextObject->GetWorld(),*CmdStr,*GLog);

	return CaptureScreenHelperInstance;
}

void UCaptureScreenHelper::ScreenshotCaptured(int32 Width, int32 Height, const TArray<FColor>& Colors)
{
	bool bSuccess = false;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	if(Format == EImageFormatType::PNG)
	{
		TArray64<uint8> CompressBitmap;
		FImageUtils::PNGCompressImageArray(Width,Height,Colors,CompressBitmap);
		bSuccess = FFileHelper::SaveArrayToFile(CompressBitmap,*ImageName);
	}

	if(Format == EImageFormatType::JPEG)
	{
		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
		if(ImageWrapper->SetRaw(Colors.GetData(),Colors.Num() * sizeof(FColor),
								Width,Height,ERGBFormat::BGRA,8))
		{
			bSuccess = FFileHelper::SaveArrayToFile(ImageWrapper->GetCompressed(Quality),*ImageName);
		}
	}

	if(bSuccess)
	{
		OnSuccess.Broadcast(ImageName);
	}else
	{
		OnFail.Broadcast(TEXT("Capture Screen Failed!"));
	}
	UGameViewportClient::OnScreenshotCaptured().Remove(DelegateHandle);
}

FString UCaptureScreenHelper::GetImageName()
{
	return this->ImageName;
}

/*void UCaptureScreenHelper::CaptureScreenshot(const int32 InWidth, const int32 InHeight, const FString CaptureName)
{
	if(GEngine && GEngine->GameViewport)
	{
		DelegateHandle =  UGameViewportClient::OnScreenshotCaptured().AddStatic(&OnScreenshotCompleteToPng);
		FString CmdStr = "HighResShot ";
		CmdStr.AppendInt(InWidth);
		CmdStr.Append("x");
		CmdStr.AppendInt(InHeight);
		GEngine->GameViewport->Exec(nullptr, *CmdStr, *GLog);
	}
}

void UCaptureScreenHelper::OnScreenshotCompleteToPng(const int32 InWidth, const int32 InHeight, const TArray<FColor>& InColor)
{
	const FDateTime CurrentTime = FDateTime::Now();
	const FString ScreenShotName = FPaths::ProjectDir()+ TEXT("/Saved/Secreen/")
										+  CurrentTime.ToFormattedString(*FString("%Y%m%d%H%M%S")) + TEXT(".png");
	TArray64<uint8> CompressBitmap;
	FImageUtils::PNGCompressImageArray(InWidth,InHeight,InColor,CompressBitmap);
	FFileHelper::SaveArrayToFile(CompressBitmap,*ScreenShotName);
	UE_LOG(LogTemp,Warning,TEXT("截图保存成功"));
	UGameViewportClient::OnScreenshotCaptured().Remove(DelegateHandle);
}

void UCaptureScreenHelper::OnScreenshotCompleteToJpg(int32 InWidth, int32 InHeight, const TArray<FColor>& InColor)
{
	const FString ScreenShotName = FPaths::ProjectContentDir()+ TEXT("test.jpg");
	IImageWrapperModule& ImageWrapperModule = FModuleManager::Get().LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	ImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	if(ImageWrapper->SetRaw(InColor.GetData(),InColor.Num() * sizeof(FColor),
								InWidth,InHeight,ERGBFormat::BGRA,8))
	{
		int32 Quality = 100;
		FFileHelper::SaveArrayToFile(ImageWrapper->GetCompressed(Quality),*ScreenShotName);
	}
	UGameViewportClient::OnScreenshotCaptured().Remove(DelegateHandle);
}*/
