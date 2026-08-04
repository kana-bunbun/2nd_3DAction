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
	/// 所持アイテムのリストを取得するためキャラクターのポインタを取得
	/// </summary>
	/// <param name="character"></param>
	void SetCharacter(Character* character) { m_character = character; }
	/// <summary>
	/// 指定した画像がアイテムスロットに合うようなスケール値を取得
	/// </summary>
	float GetNormalizeGraphScale(int graphHandle);
private:
	Character* m_character;
	/// <summary>
	/// 自身のスロット番号
	/// </summary>
	int m_slotID;
	/// <summary>
	/// アイテムスロット背景の画像
	/// </summary>
	std::shared_ptr<ImageResource>m_backGroundImage;


};

