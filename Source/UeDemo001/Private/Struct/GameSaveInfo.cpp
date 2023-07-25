#include "Struct/GameSaveInfo.h"

FGameSaveInfo::FGameSaveInfo()
{
	this->CharacterInfo = FCharacterInfo();
	this->SaveName = "DefaultSave";
	this->SaveDate = FDateTime::Now().ToFormattedString(*FString("%Y-%m-%d %H:%M:%S"));
	this->TotalCostTime = 0;
}
