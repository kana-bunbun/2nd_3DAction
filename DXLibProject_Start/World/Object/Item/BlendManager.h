#pragma once
#include<array>
#include<vector>
#include<string>
class BlendManager {
public:
	enum class Type {
		Invalid = -1,
		Apple,
		Beer,
		Bread,
		Cheese,
		CheeseBread,
		Max,
	};


	BlendManager();
	~BlendManager();
public:
	const BlendManager::Type& Blend(const BlendManager::Type& base, const BlendManager::Type& add);
	void Debug();
private:
	void LoadRecipe( std::vector<std::vector<std::string>> loadData);
	BlendManager::Type SToItemType(std::string name);
	std::string ItemTypeToS(const BlendManager::Type& type)const;
private:
	std::array <std::array<int, static_cast<int>(BlendManager::Type::Max)>, static_cast<int>(BlendManager::Type::Max)> ItemRecipe;
};