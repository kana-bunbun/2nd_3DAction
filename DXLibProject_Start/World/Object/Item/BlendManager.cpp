#include "BlendManager.h"
#include"../../../Utility/Loder/CsvLoader.h"
#include"../../../Utility/Loder/Data.h"
#include"../../../Data/BlendRecipe.h"

#include<DxLib.h>
namespace {
	constexpr int kTypeMax = static_cast<int>(ItemData::Type::Max);

	const char* const ItemName[kTypeMax]{
		"Honey",
		"Jam",
		"ChiliPepper",
		"Whiskey",
		"HealBottle",
		"MolotovCocktail",
	};
}
BlendManager& BlendManager::GetInstnce()
{
	static BlendManager instance;
	return instance;
}
void BlendManager::Init()
{
	m_itemRecipe = Data::Csv::LoadCsvAs<BlendRecipe>("ItemRecipe");

}

BlendManager::~BlendManager()
{

}

const ItemData::Type& BlendManager::Blend(const ItemData::Type& base, const ItemData::Type& add)
{
	if (static_cast<int>(base) < 0 || static_cast<int>(base) > static_cast<int>(ItemData::Type::Max))return ItemData::Type::Invalid;
	if (static_cast<int>(add) < 0 || static_cast<int>(add) > static_cast<int>(ItemData::Type::Max))return ItemData::Type::Invalid;
	int castValue = static_cast<int>(m_itemRecipe[static_cast<int>(base)].blendRecipe[static_cast<int>(add)]);
	if (castValue<0 || castValue>kTypeMax)return ItemData::Type::Invalid;
		ItemData::Type result = static_cast<ItemData::Type>(castValue);


	return result;
}

void BlendManager::Debug()
{
	for (int i = 0; i < kTypeMax; i++) {
		ItemData::Type base = static_cast<ItemData::Type>(i);
		for (int j = 0; j < kTypeMax; j++) {
			ItemData::Type add = static_cast<ItemData::Type>(j);
			ItemData::Type result = Blend(base, add);
			if (result == ItemData::Type::Invalid)continue;
			printfDx("%s + %s = %s\n", BlendRecipe::ItemTypeToS(base).c_str(), BlendRecipe::ItemTypeToS(add).c_str(), BlendRecipe::ItemTypeToS(result).c_str());
		}
	}
}
