#pragma once
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
	const ItemBase::Type& Blend(ItemBase::Type base, ItemBase::Type add)const;
	ItemBase::Type type;
	ItemBase::Type operator+(ItemBase::Type add);	// アイテムの加算
	ItemBase::Type& operator+=(ItemBase::Type add);	// ベクトルの加算代入演算子
};