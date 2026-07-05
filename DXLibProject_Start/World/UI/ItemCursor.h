#pragma once
#include"../../Utility/Input.h"
#include"../../Utility/Vector3.h"
#include"../Object/Item/BlendManager.h"
#include<array>
#include<memory>
namespace {
	// スロットの個数
	constexpr int kSlotMax = 10;
	constexpr int kSelectMax = 2;
}
class ItemSlot;
class Player;
class Item;
class ItemObjectManager;
class ItemCursor
{
public:

	//struct Item {
	//public:
	//	Item(ItemBase::Type type) :m_type(type),m_holdNum(0),m_select(false){}
	//	ItemBase::Type m_type;
	//	int m_holdNum;
	//	bool m_select;
	//};

public:
	ItemCursor();
	~ItemCursor();
	void Init();
	void End();
	void Update();
	// カーソルの座標補間の更新処理
	void UpdateCursor();
	// 入力による更新処理
	void UpdateToInput();
	// 選択中インデックスの正規化
	void NormalizeIndex();
	// アイテムを使う処理
	void UseItem();
	void Draw();

	Vector3 GetSelectPos(int selectIndex);

	bool AddItem(const BlendManager::Type& type);
	bool SubItem(const BlendManager::Type& type);

	// アイテムを選択する関数
	void Select();
	// カーソルがあっているスロットの選択状況を変更する関数
	void ChangeSelectFlag(size_t index);
	// キャンセルする関数
	void Cancel();
	void Cancel(const BlendManager::Type& type);
public:
	bool GetIsBlendMenu() { return m_isBlendMenu; }
	void SetIsBlendMenu(bool isblend) { m_isBlendMenu = isblend; }
	void SetPad(Input::Pad pad) { m_pad = pad; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void SetItemObjectManager(ItemObjectManager* pItemObjectManager) { m_pItemObjectManager = pItemObjectManager; }
private:
	bool BlendItem();
private:
	// 内部の選択中インデックス
	int m_selectIndex;
	// 見た目上の選択インデックス
	int m_showSelectIndex;
	// カーソル画像のグラフィックハンドル
	int m_cursorHandle;
	// カーソルの描画座標
	Vector3 m_cursorPosition;
	// 割り当てられたコントローラー
	Input::Pad m_pad;
	// 所持しているアイテムの種類
	std::array < ItemSlot*, kSlotMax > m_slots;
	std::array<BlendManager::Type, kSelectMax>m_selected;
	// アイテム合成メニュ―かどうか
	bool m_isBlendMenu;

	float m_holdLeftCount;
	float m_holdRightCount;

	Player* m_pPlayer;
	ItemObjectManager* m_pItemObjectManager;
};

