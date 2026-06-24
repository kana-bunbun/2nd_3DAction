#pragma once
#include"../../Utility/Input.h"
#include"../../Utility/Vector3.h"
#include<array>
namespace {
	// スロットの個数
	constexpr int kSlotMax = 10;
}
class ItemCursor
{
public:
	enum class ItemType {
		Invalid=-1,
		Apple,
		Beer,
		Bread,
		Cheese,
		Max,
	};
	class Item {
	public:
		Item(const ItemType& type):m_type(type),m_holdNum(1),m_select(false){}
		ItemType m_type;
		int m_holdNum;
		bool m_select;
	};
public:
	ItemCursor();
	~ItemCursor();
	void Init();
	void End();
	void Update(float deltaTime);
	// カーソルの座標補間の更新処理
	void UpdateCursor(float deltaTime);
	// 入力による更新処理
	void UpdateToInput();
	// 選択中インデックスの正規化
	void NormalizeIndex();
	// アイテムを使う処理
	void UseItem();
	void Draw();

	Vector3 GetSelectPos(int selectIndex);

	bool AddItem(const ItemType& type);
public:
	void SetPad(Input::Pad pad) { m_pad = pad; }
private:
	// 背景画像のグラフィックハンドル
	int m_backGroundHandle;
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
	std::array<Item*, kSlotMax> m_itemArray;
	// アイテムのグラフィックハンドル
	std::array<int, static_cast<int>(ItemType::Max)>m_itemHandles;
};

