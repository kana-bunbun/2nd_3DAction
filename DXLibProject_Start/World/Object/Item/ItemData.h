#pragma once
struct ItemData
{
public:
	enum class Type {
		Invalid = -1,
		Honey,
		Jam,
		Pepper,
		Whiskey,
		HealBottle,
		MolotovCocktail,
		Max,
	};
	Type m_type;
};