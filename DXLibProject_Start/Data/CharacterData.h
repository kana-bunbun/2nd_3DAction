#pragma once
#include"pch.h"
#include"Utility/MyMath.h"

struct CharacterData
{
public:
	void Init(int paramID);
	void Reset();
	void RemoveHP(int damage) { HP = MyMath::Clamp(HP - damage, 0, MaxHP); }
	void RemoveHPRatio(float ratio);
	void AddHP(int damage) { HP = MyMath::Clamp(HP + damage, 0, MaxHP); }
	void AddHPRatio(float ratio);
	void RemoveMP(int damage) { MP = MyMath::Clamp(MP - damage, 0, MaxMP); }
	void RemoveMPRatio(float ratio);
	void AddMP(int damage) { MP = MyMath::Clamp(MP + damage, 0, MaxMP); }
	void AddMPRatio(float ratio);

public:
	int ID=-1;
	int MaxHP=1;
	int HP=0;
	int MaxMP=0;
	int MP=0;
};