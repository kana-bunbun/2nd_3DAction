#pragma once
#include "../GameObject.h"
#include"../Object/Item/ItemList.h"
#include<functional>
class Character :public GameObject
{
public:
	enum class Type {
		Invalid = -1,
		Player,
		Enemy,
		Dragon,
	};
public:
	// キャラクター種類の取得
	virtual const Type& GetCharacterType() {
		return Type::Player;
	}
	// キャラクターのID
	int m_ID;
	virtual void Setup(){}
	ItemList* GetItemList() { return m_itemList.get(); }
	// アイテムの追加処理を取得する
	const std::function<void(const ItemData::Type&, int)>& GetAddItem();
	// アイテムの消費処理を取得する
	const std::function<void(int, int)>& GetSubItem();
protected:
	std::unique_ptr<ItemList> m_itemList;
};

