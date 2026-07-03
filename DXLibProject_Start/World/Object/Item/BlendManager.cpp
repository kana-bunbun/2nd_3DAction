#include "BlendManager.h"
#include"../../../Utility/CsvLoader.h"
#include<DxLib.h>
namespace {
	constexpr int kTypeMax = static_cast<int>(BlendManager::Type::Max);
	constexpr BlendManager::Type kBlendRecipe[kTypeMax][kTypeMax] = {
		{BlendManager::Type::Invalid},		//Appleの組み合わせ
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

const BlendManager::Type& BlendManager::Blend(const BlendManager::Type& base, const BlendManager::Type& add)
{
	if (static_cast<int>(base) < 0 || static_cast<int>(base) > static_cast<int>(BlendManager::Type::Max))return BlendManager::Type::Invalid;
	if (static_cast<int>(add) < 0 || static_cast<int>(add) > static_cast<int>(BlendManager::Type::Max))return BlendManager::Type::Invalid;
	int castValue = ItemRecipe[static_cast<int>(base)][static_cast<int>(add)];
	if (castValue<0 || castValue>kTypeMax)return BlendManager::Type::Invalid;
		BlendManager::Type result = static_cast<BlendManager::Type>(castValue);


	return result;
}

void BlendManager::Debug()
{
	for (int i = 0; i < kTypeMax; i++) {
			BlendManager::Type base = static_cast<BlendManager::Type>(i);
		for (int j = 0; j < kTypeMax; j++) {
			BlendManager::Type add = static_cast<BlendManager::Type>(j);
			BlendManager::Type result = Blend(base, add);

			printfDx("%s + %s = %s\n", ItemTypeToS(base).c_str(), ItemTypeToS(add).c_str(), ItemTypeToS(result).c_str());
		}
	}
}

void BlendManager::LoadRecipe(std::vector<std::vector<std::string>> loadData)
{
	for (int i = 0; i < loadData[0].size(); i++) {
		if (i % 3 != 0)continue;
		BlendManager::Type base = SToItemType(loadData[0][i+1]);
		for (int j = 0; j < kTypeMax; j++) {
			int itemIndex = j + 1;
			BlendManager::Type add = SToItemType(loadData[itemIndex][i]);
			BlendManager::Type result = SToItemType(loadData[itemIndex][i+1]);
			ItemRecipe[static_cast<int>(base)][static_cast<int>(add)] = static_cast<int>(result);

		}
	}
}

BlendManager::Type BlendManager::SToItemType(std::string name)
{
	BlendManager::Type result = Type::Invalid;

	for (int i = 0; i < kTypeMax; i++) {
		std::string typeName = ItemName[i];
		if (name != typeName)continue;
		result = static_cast<BlendManager::Type>(i);
		return result;
	}
	return result;
}

std::string BlendManager::ItemTypeToS(const BlendManager::Type& type) const
{
	std::string result = "";

	for (int i = 0; i < kTypeMax; i++) {
		if (type != static_cast<BlendManager::Type >(i) )continue;
		result = ItemName[i];
		return result;
	}
	return result;
}

