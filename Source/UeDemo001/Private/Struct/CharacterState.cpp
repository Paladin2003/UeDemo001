#include "Struct/CharacterState.h"

FCharacterState::FCharacterState()
{
}

FCharacterState::FCharacterState(int32 Hp, int32 Mp)
{
	this->CurHp = this->MaxHp = Hp;
	this->CurMp = this->MaxMp = Mp;
}

FCharacterState& FCharacterState::operator+=(const FCharacterState& InState)
{
	UE_LOG(LogTemp,Warning,TEXT("FCharacterState::operator:%d===%d"),InState.CurHp,InState.CurMp);
	this->CurHp += InState.CurHp;
	if (this->CurHp >= this->MaxHp)
	{
		this->CurHp = MaxHp;
	}
	if(this->CurHp <= 0)
	{
		this->CurHp = 0;
	}

	this->CurMp += InState.CurMp;
	
	if (this->CurMp >= this->MaxMp)
	{
		this->CurMp = this->MaxMp;
	}
	if(this->CurMp <= 0)
	{
		this->CurMp = 0;
	}
	UE_LOG(LogTemp,Warning,TEXT("FCharacterState::operator:%d===%d"),this->CurHp,this->CurMp);
	return *this;
}
