#pragma once
#include"pch.h"
#include"../Core/UIObject.h"
#include"World/Object/Item/ItemData.h"
#include"World/Component/Transform.h"
#include"Utility/Vector3.h"
class Character;
class ImageResource;
/// <summary>
/// アイテムスロット1項目単体のUI表示クラス
/// </summary>
class UIItemSlot:public UIObject
{
public:
	UIItemSlot(int ID);
	~UIItemSlot();
	/// <summary>
	/// 個別の描画処理
	/// </summary>
	void OnDraw()override;
	/// <summary>
	/// 所持アイテムのリストを設定
	/// </summary>
	void SetItemData(const ItemData& itemData) { m_itemData= itemData; }
	/// <summary>
	/// 所持アイテムの消費
	/// </summary>
	void ConsumeItem(const Transform& transform);
	/// <summary>
	/// 所持アイテムの選択
	/// </summary>
	/// <returns>選択したらtrue,キャンセルしたらfalse</returns>
	bool Select();
	/// <summary>
	/// 所持アイテムの選択状況のキャンセル
	/// </summary>
	void Cancel();
	/// <summary>
	/// 指定した画像がアイテムスロットに合うようなスケール値を取得
	/// </summary>
	float GetNormalizeGraphScale(int graphHandle);
	int GetID() { return m_slotID; }
	/// <summary>
	/// アイテムを取得しているかどうかを取得
	/// </summary>
	/// <returns></returns>
	bool Exists() { return m_itemData.GetType() != ItemData::Type::Invalid; }
	ItemData GetItemData()const{ return m_itemData; }
private:
	ItemData m_itemData;
	/// <summary>
	/// 自身のスロット番号
	/// </summary>
	int m_slotID;
	/// <summary>
	/// アイテムスロット背景の画像
	/// </summary>
	std::shared_ptr<ImageResource>m_backGroundImage;
	/// <summary>
	/// 選択しているかどうか
	/// </summary>
	bool m_isSelect;


};

