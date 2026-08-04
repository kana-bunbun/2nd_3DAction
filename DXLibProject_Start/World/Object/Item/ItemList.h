#pragma once
#include"ItemData.h"
#include<array>

namespace {
	// アイテムスロットの個数
	constexpr int kItemSlotNum = 10;
}

class ItemList
{
public:
	ItemList();
	~ItemList();

	/// <summary>
	/// アイテムを配列に追加する処理
	/// </summary>
	/// <param name="type"></param>
	/// <param name="addNum"></param>
	void AddItem(const ItemData::Type& type, int addNum = 1);
	/// <summary>
	/// アイテムを獲得できるかどうか取得
	/// </summary>
	/// <param name="type">獲得していアイテムの種類</param>
	/// <returns></returns>
	bool CanAddItem(const ItemData::Type& type);
	/// <summary>
	/// アイテムの消費処理
	/// </summary>
	/// <param name="itemIndex">配列の番号</param>
	/// <param name="subNum">消費量</param>
	void UseItem(int itemIndex, int subNum = 1);
	/// <summary>
	/// 指定した番号のアイテム使用可能かどうかを取得
	/// </summary>
	/// <param name="itemIndex">配列の番号</param>
	/// <param name="useCount">消費量</param>
	/// <returns></returns>
	bool CanUseItem(int itemIndex,int useCount);

	const std::array<ItemData, kItemSlotNum> GetItemData() { return m_items; }
private:
	/// <summary>
	/// 所持しているアイテムの配列
	/// </summary>
	std::array<ItemData, kItemSlotNum> m_items;

};

