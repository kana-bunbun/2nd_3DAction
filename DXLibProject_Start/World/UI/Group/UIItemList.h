#pragma once
#include"../Object/UIItemSlot.h"
#include"../../Object/Item/ItemList.h"
#include"../Core/UIObject.h"
#include<array>
#include<memory>
class UIItemCursor;
/// <summary>
/// プレイヤーの所持アイテムリストのUI表示をする
/// </summary>
class UIItemList: public UIObject
{
public:
	UIItemList();


	void OnInit()override;
	void OnUpdate(float deltatime)override;
	/// <summary>
	/// 1つ後の項目を設定する
	/// </summary>
	void SelectPrevIndex();
	/// <summary>
	/// 1つ後の項目を設定する
	/// </summary>
	void SelectNextIndex();
	/// <summary>
	/// 指定した番号のスロットの座標を求める
	/// </summary>
	const Vector2& CalculateSlotPos(int slotID);
private:
	/// <summary>
	/// 選択中のインデックス
	/// </summary>
	int m_selectIndex;
	/// <summary>
	/// 自身が管理するスロットの配列
	/// </summary>
	std::array<UIItemSlot*, kItemSlotNum> m_itemSlots;
	/// <summary>
	/// 自身が管理するアイテムカーソル
	/// </summary>
	UIItemCursor* m_pItemCursor;
};

