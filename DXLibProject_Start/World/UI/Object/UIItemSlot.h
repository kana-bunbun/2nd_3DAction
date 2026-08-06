#pragma once
#include"../Core/UIObject.h"
#include"../../../World/Object/Item/ItemData.h"
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
	/// 指定した画像がアイテムスロットに合うようなスケール値を取得
	/// </summary>
	float GetNormalizeGraphScale(int graphHandle);
	int GetID() { return m_slotID; }
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


};

