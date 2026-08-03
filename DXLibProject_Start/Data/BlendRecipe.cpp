#include "BlendRecipe.h"

namespace {
	const char* const ItemName[static_cast<int>(ItemData::Type::Max)]{
	"Honey",
	"Jam",
	"ChiliPepper",
	"Whiskey",
	"HealBottle",
	"MolotovCocktail",
	};
}

ItemData::Type BlendRecipe::SToItemType(std::string name)
{
	ItemData::Type itemType = ItemData::Type::Invalid;
	
	for (int i = 0; i < static_cast<int>(ItemData::Type::Max); i++) {
		std::string typeName = ItemName[i];
		if (name != typeName)continue;
		itemType = static_cast<ItemData::Type>(i);
		return itemType;
	}
	return itemType;
}

std::string BlendRecipe::ItemTypeToS(const ItemData::Type& type) 
{
	std::string itemName = "";

	for (int i = 0; i < static_cast<int>(ItemData::Type::Max); i++) {
		if (type != static_cast<ItemData::Type>(i))continue;
		itemName = ItemName[i];
		return itemName;
	}
	return itemName;
}
