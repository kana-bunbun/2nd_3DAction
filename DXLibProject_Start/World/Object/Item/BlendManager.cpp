#include "BlendManager.h"
#include"../../../Utility/CsvLoader.h"
#include<DxLib.h>
namespace {
	constexpr int kTypeMax = static_cast<int>(ItemData::Type::Max);
	constexpr ItemData::Type kBlendRecipe[kTypeMax][kTypeMax] = {
		{ItemData::Type::Invalid},		//Appleの組み合わせ
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
BlendManager& BlendManager::GetInstnce()
{
	static BlendManager instance;
	return instance;
}
void BlendManager::Init()
{
	CsvLoader loadData = CsvLoader("ItemRecipe.csv");
	LoadRecipe(loadData.GetLoadData());

}

BlendManager::~BlendManager()
{
	for (auto& recipe : ItemRecipe) {
		recipe.fill(-1);
	}
}

const ItemData::Type& BlendManager::Blend(const ItemData::Type& base, const ItemData::Type& add)
{
	if (static_cast<int>(base) < 0 || static_cast<int>(base) > static_cast<int>(ItemData::Type::Max))return ItemData::Type::Invalid;
	if (static_cast<int>(add) < 0 || static_cast<int>(add) > static_cast<int>(ItemData::Type::Max))return ItemData::Type::Invalid;
	int castValue = ItemRecipe[static_cast<int>(base)][static_cast<int>(add)];
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

			printfDx("%s + %s = %s\n", ItemTypeToS(base).c_str(), ItemTypeToS(add).c_str(), ItemTypeToS(result).c_str());
		}
	}
}

void BlendManager::LoadRecipe(std::vector<std::vector<std::string>> loadData)
{
	for (int i = 0; i < loadData[0].size(); i++) {
		if (i % 3 != 0)continue;
		ItemData::Type base = SToItemType(loadData[0][i+1]);
		for (int j = 0; j < kTypeMax; j++) {
			int itemIndex = j + 1;
			ItemData::Type add = SToItemType(loadData[itemIndex][i]);
			ItemData::Type result = SToItemType(loadData[itemIndex][i+1]);
			ItemRecipe[static_cast<int>(base)][static_cast<int>(add)] = static_cast<int>(result);

		}
	}
}

ItemData::Type BlendManager::SToItemType(std::string name)
{
	ItemData::Type result = ItemData::Type::Invalid;

	for (int i = 0; i < kTypeMax; i++) {
		std::string typeName = ItemName[i];
		if (name != typeName)continue;
		result = static_cast<ItemData::Type>(i);
		return result;
	}
	return result;
}

std::string BlendManager::ItemTypeToS(const ItemData::Type& type) const
{
	std::string result = "";

	for (int i = 0; i < kTypeMax; i++) {
		if (type != static_cast<ItemData::Type >(i) )continue;
		result = ItemName[i];
		return result;
	}
	return result;
}

