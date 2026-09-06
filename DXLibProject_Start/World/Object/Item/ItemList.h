#pragma once
#include"pch.h"

#include"ItemData.h"

namespace {
	// アイテムスロットの個数
	constexpr int kItemSlotMax = 10;
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
	/// <summary>
	/// 配列内の指定IDのアイテム情報取得
	/// </summary>
	const ItemData& GetItemData(int ID)const;
	void Debug();
private:
	/// <summary>
	/// 所持しているアイテムの配列
	/// </summary>
	std::array<ItemData, kItemSlotMax> m_items;

};

