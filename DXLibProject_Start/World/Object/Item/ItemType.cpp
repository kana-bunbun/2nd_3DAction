#include "ItemType.h"
#include"../../../Utility/CsvLoader.h"
#include<DxLib.h>
namespace {
	constexpr int kTypeMax = static_cast<int>(ItemBase::Type::Max);
	constexpr ItemBase::Type kBlendRecipe[kTypeMax][kTypeMax] = {
		{ItemBase::Type::Invalid},		//Appleの組み合わせ
		{},		//Beerの組み合わせ
		{},		//Breadの組み合わせ
		{},		//Cheeseの組み合わせ
		{},		//CheeseBreadの組み合わせ

	};
	const char* const ItemName[kTypeMax]{
		"Apple",
		"Beer",
		"Bread",
		"Cheese",
		"CheeseBread",
	};
}
ItemBase::ItemBase()
{
	CsvLoader Ki = CsvLoader("ItemRecipe.csv");
	LoadRecipe(Ki.GetLoadData());
}

ItemBase::~ItemBase()
{
	for (auto& recipe : ItemRecipe) {
		recipe.fill(-1);
	}
}

const ItemBase::Type& ItemBase::Blend(const ItemBase::Type& base, const ItemBase::Type& add)
{
	int castValue = ItemRecipe[static_cast<int>(base)][static_cast<int>(add)];
	if (castValue<0 || castValue>kTypeMax)return ItemBase::Type::Invalid;
		ItemBase::Type result = static_cast<ItemBase::Type>(castValue);


	return result;
}

void ItemBase::Debug()
{
	for (int i = 0; i < kTypeMax; i++) {
		for (int j = 0; j < kTypeMax; j++) {
			ItemBase::Type base = static_cast<ItemBase::Type>(i);
			ItemBase::Type add = static_cast<ItemBase::Type>(j);
			ItemBase::Type result = Blend(base, add);

			printfDx("%s + %s = %s\n", ItemTypeToS(base).c_str(), ItemTypeToS(add).c_str(), ItemTypeToS(result).c_str());
		}
	}
}

void ItemBase::LoadRecipe(std::vector<std::vector<std::string>> loadData)
{
	for (int i = 0; i < loadData[0].size(); i++) {
		if (i % 3 != 0)continue;
		ItemBase::Type base = SToItemType(loadData[0][i+1]);
		for (int j = 0; j < kTypeMax; j++) {
			int itemIndex = j + 1;
			ItemBase::Type add = SToItemType(loadData[itemIndex][i]);
			ItemBase::Type result = SToItemType(loadData[itemIndex][i+1]);
			ItemRecipe[static_cast<int>(base)][static_cast<int>(add)] = static_cast<int>(result);

		}
	}
}

ItemBase::Type ItemBase::SToItemType(std::string name)
{
	ItemBase::Type result = Type::Invalid;

	for (int i = 0; i < kTypeMax; i++) {
		std::string typeName = ItemName[i];
		if (name != typeName)continue;
		result = static_cast<ItemBase::Type>(i);
		return result;
	}
	return result;
}

std::string ItemBase::ItemTypeToS(const ItemBase::Type& type) const
{
	std::string result = "";

	for (int i = 0; i < kTypeMax; i++) {
		if (type != static_cast<ItemBase::Type >(i) )continue;
		result = ItemName[i];
		return result;
	}
	return result;
}

