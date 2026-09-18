#pragma once
#include"Utility/MyMath.h"
struct CharacterParam
{
public:
	void HPDamage(int damage) { HP = MyMath::Clamp(HP - damage, 0, MaxHP); }
	void HPRatioDamage(float ratio);
	void MPDamage(int damage) { MP = MyMath::Clamp(MP - damage, 0, MaxMP); }
	void MPRatioDamage(float ratio);
public:
	int MaxHP=1;
	int HP=1;
	int MaxMP=1;
	int MP=1;
	int attack=1;
	int deffence=1;
	int Speed=1;
};

