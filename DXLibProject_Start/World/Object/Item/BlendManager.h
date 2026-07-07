#pragma once
#include<array>
#include<vector>
#include<string>
#include"ItemData.h"
class BlendManager {
public:

	static BlendManager& GetInstnce();
	void Init();
public:
	~BlendManager();
	const ItemData::Type& Blend(const ItemData::Type& base, const ItemData::Type& add);
	void Debug();
private:
	void LoadRecipe( std::vector<std::vector<std::string>> loadData);
	ItemData::Type SToItemType(std::string name);
	std::string ItemTypeToS(const ItemData::Type& type)const;
private:
	BlendManager()=default;
	BlendManager(const BlendManager&)=delete;
	BlendManager& operator=(const BlendManager&) = delete;
	BlendManager(BlendManager&&) = delete;
	BlendManager& operator=(const BlendManager&&) = delete;
private:
	std::array <std::array<int, static_cast<int>(ItemData::Type::Max)>, static_cast<int>(ItemData::Type::Max)> ItemRecipe;
};