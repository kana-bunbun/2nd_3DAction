#pragma once
#include<array>

struct ItemData
{
public:
	enum class Type {
		Invalid = -1,
		Honey,
		Jam,
		ChiliPepper,
		Whiskey,
		HealBottle,
		MolotovCocktail,
		Max,
	};
	// アイテムの種類を取得
	const Type& GetType() { return m_type; }
	// アイテムの種類を設定
	void SetType(const Type& type) { m_type = m_type; }
	// アイテムの所持数を取得
	int GetItemNum() { return m_num; }
	// 所持数に加算
	void Add(int addVallue = 1) { m_num += addVallue; }
	// 所持数から減らす
	void Sub(int subVallue = 1) { m_num -= subVallue; }
	// 使用できるかどうか
	bool CanUse(int useCount = 1) { return m_num >= useCount; }
private:
	// 自身の種類
	Type m_type = Type::Invalid;
	// 所持数
	int m_num = 0;
};