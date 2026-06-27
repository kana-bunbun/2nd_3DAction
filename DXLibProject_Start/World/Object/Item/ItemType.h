#pragma once
#include<array>
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

public:
	static const ItemBase::Type& Blend(const ItemBase::Type& base, const ItemBase::Type& add);

	static std::array <std::array<int, static_cast<int>(ItemBase::Type::Max)>, static_cast<int>(ItemBase::Type::Max)> ItemRecipe;
};