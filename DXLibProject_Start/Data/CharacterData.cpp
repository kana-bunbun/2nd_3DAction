#include "pch.h"
#include "CharacterData.h"
#include "System/CharacterDataManager.h"

void CharacterData::Init(int paramID)
{
	CharacterData data=CharacterDataManager::GetInstance().GetCharacterData(paramID);

	MaxHP = data.MaxHP;
	HP = data.HP;
	MaxMP = data.MaxMP;
	MP = data.MP;
	
}

void CharacterData::Reset()
{
	HP = MaxHP;
	MP = MaxMP;
}

void CharacterData::RemoveHPRatio(float ratio)
{
	// 最大HPに対する割合を計算(切り上げ)
	int damage = std::ceil(MaxHP*MyMath::Clamp(ratio, 0.0f, 1.0f));
	// ダメージ処理
	 HP = MyMath::Clamp(HP - damage, 0, MaxHP); 
}

void CharacterData::AddHPRatio(float ratio)
{
	// 最大HPに対する割合を計算(切り上げ)
	int damage = std::ceil(MaxHP * MyMath::Clamp(ratio, 0.0f, 1.0f));
	// ダメージ処理
	HP = MyMath::Clamp(HP + damage, 0, MaxHP);
}

void CharacterData::RemoveMPRatio(float ratio)
{
	// 最大HPに対する割合を計算(切り上げ)
	int damage = std::ceil(MaxHP * MyMath::Clamp(ratio, 0.0f, 1.0f));
	// ダメージ処理
	HP = MyMath::Clamp(HP - damage, 0, MaxHP);
}

void CharacterData::AddMPRatio(float ratio)
{
	// 最大HPに対する割合を計算(切り上げ)
	int damage = std::ceil(MaxHP * MyMath::Clamp(ratio, 0.0f, 1.0f));
	// ダメージ処理
	HP = MyMath::Clamp(HP + damage, 0, MaxHP);
}
