#pragma once
#include<array>
#include<vector>
#include<string>
class ItemBase {
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


	ItemBase();
	~ItemBase();
public:
	const ItemBase::Type& Blend(const ItemBase::Type& base, const ItemBase::Type& add);
	void Debug();
private:
	void LoadRecipe( std::vector<std::vector<std::string>> loadData);
	ItemBase::Type SToItemType(std::string name);
	std::string ItemTypeToS(const ItemBase::Type& type)const;
private:
	std::array <std::array<int, static_cast<int>(ItemBase::Type::Max)>, static_cast<int>(ItemBase::Type::Max)> ItemRecipe;
};