#pragma once
#include"ItemData.h"
#include<array>
#include<vector>
#include<string>
struct BlendRecipe {
public:
	// 合成レシピ
	std::array<ItemData::Type, static_cast<int>(ItemData::Type::Max)>blendRecipe;
	static ItemData::Type SToItemType(std::string name);
	static std::string ItemTypeToS(const ItemData::Type& type);
};