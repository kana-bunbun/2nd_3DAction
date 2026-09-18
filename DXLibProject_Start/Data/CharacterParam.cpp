#include "CharacterParam.h"
#include "pch.h"
#include "CharacterParam.h"

void CharacterParam::HPRatioDamage(float ratio)
{
	// 最大HPに対する割合を計算(切り上げ)
	int damage = std::ceil(MaxHP*MyMath::Clamp(ratio, 0.0f, 1.0f));
	// ダメージ処理
	 HP = MyMath::Clamp(HP - damage, 0, MaxHP); 
}

void CharacterParam::MPRatioDamage(float ratio)
{
	// 最大HPに対する割合を計算(切り上げ)
	int damage = std::ceil(MaxHP * MyMath::Clamp(ratio, 0.0f, 1.0f));
	// ダメージ処理
	HP = MyMath::Clamp(HP - damage, 0, MaxHP);
}
