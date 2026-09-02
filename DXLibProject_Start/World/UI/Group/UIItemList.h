#pragma once
#include"../Object/UIItemSlot.h"
#include"../../Object/Item/ItemList.h"
#include"../Core/UIObject.h"
#include"World/Action/ActionInterval.h"
#include"Utility/MyMath.h"
#include<array>
#include<memory>
class UIItemCursor;
class ActionInterval;
/// <summary>
/// プレイヤーの所持アイテムリストのUI表示をする
/// </summary>
class UIItemList: public UIObject
{
public:
	UIItemList();


	void OnInit()override;
	void OnUpdate(float deltatime, const InputData& inputData)override;
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
	/// ベクトル指定のカーソル移動処理
	/// </summary>
	/// <param name="inputVector">入力した量</param>
	void MoveCursor(const Vector2& inputVector);
	/// <summary>
	/// 4方向指定のカーソル移動処理
	/// </summary>
	/// <param name="direction">入力した方向</param>
	void MoveCursor(const DirectionFour& direction);
private:
	/// <summary>
	/// 選択中のインデックス
	/// </summary>
	int m_selectIndex;
	/// <summary>
	/// 自身が管理するスロットの配列
	/// </summary>
	std::array<UIItemSlot*, kItemSlotMax> m_itemSlots;
	/// <summary>
	/// 自身が管理するアイテムカーソル
	/// </summary>
	UIItemCursor* m_pItemCursor;
	/// <summary>
	/// カーソル移動のインターバル
	/// </summary>
	ActionInterval m_cursorInterval;
};

