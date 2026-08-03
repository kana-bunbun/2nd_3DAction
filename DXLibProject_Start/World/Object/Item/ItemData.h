#pragma once
#include<array>

struct ItemData
{
public:
	enum class Type {
		Invalid = -1,
		Honey,
		Jam,
		ChiliPepper,
		Whiskey,
		HealBottle,
		MolotovCocktail,
		Max,
	};
	Type m_type;
};