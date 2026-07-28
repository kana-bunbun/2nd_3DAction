#pragma once
#include"../../GameObjectManager.h"
#include<vector>
#include<memory>
#include <type_traits>
#include"ItemObjectBase.h"
class GameObject;
class ItemCursor;
class ItemObjectManager
{
public:
	ItemObjectManager();
	~ItemObjectManager();

	void Init();
	void End();
	void Update();
	void Draw();
	// アイテム生成
	template<class T>
	T* CreateItem(GameObject* obj);
	// アイテム呼び出し
	template<class T>
	void CallItem(GameObject* obj);
	void SetupItem(ItemObjectBase* item, GameObject* obj);
public:
	ItemCursor* GetItemCursor() { return m_pItemCursor.get(); }
	
private:
	// 自身が管理するアイテムオブジェクトの配列
	std::vector<ItemObjectBase*>m_items;
	// アイテムカーソル
	std::unique_ptr<ItemCursor> m_pItemCursor;
};

template<class T>
inline T* ItemObjectManager::CreateItem(GameObject* obj)
{
	// 継承チェック
	static_assert(std::is_base_of<ItemObjectBase, T>::value, "アイテム生成:アイテムの基底クラスを未継承");
	// オブジェクト生成
	auto item = GameObjectManager::GetInstance().CreateObject<T>();
	SetupItem(item, obj);

	// 配列に追加
	m_items.push_back(item);
	return item;
}

template<class T>
inline void ItemObjectManager::CallItem(GameObject* obj)
{
	// 継承チェック
	static_assert(std::is_base_of<ItemObjectBase, T>::value, "アイテム呼び出し:アイテムの基底クラスを未継承");
	// 再利用できるオブジェクトを探す
	for (int i = 0; i < m_items.size();i++) {
		// nullチェック
		if (!m_items[i])continue;
		// 使用中でないオブジェクトを探す
		if (m_items[i]->IsUsing())continue;
		// 同じクラスかどうかチェック
		if (!dynamic_cast<T*>(m_items[i])) continue;
		//if (!std::is_same < T, typeid(item) > ::value)continue;
		// アイテムのセットアップ
		m_items[i]->Setup(obj->GetTransform());
		
		return;
	}

	// 再利用できるオブジェクトがなければ
	auto item=CreateItem<T>(obj);

	return;
}
