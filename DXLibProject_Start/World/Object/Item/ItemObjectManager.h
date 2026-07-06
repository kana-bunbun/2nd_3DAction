#pragma once
#include"../../GameObjectManager.h"
#include<vector>
#include<memory>
#include <type_traits>
class GameObject;
class ItemObject;
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
	void SetupItem(ItemObject* item, GameObject* obj);
public:
	ItemCursor* GetItemCursor() { return m_pItemCursor.get(); }
	void SetGameObjectManager(GameObjectManager* pGameObjectManager) { m_pGameObjectManager = pGameObjectManager; }
private:
	// 自身が管理するアイテムオブジェクトの配列
	std::vector<ItemObject*>m_items;
	// ゲームオブジェクト管理をするポインタ
	GameObjectManager* m_pGameObjectManager;
	// アイテムカーソル
	std::unique_ptr<ItemCursor> m_pItemCursor;
};

template<class T>
inline T* ItemObjectManager::CreateItem(GameObject* obj)
{
	// 継承チェック
	static_assert(std::is_base_of<ItemObject, T>::value, "アイテム生成:アイテムの基底クラスを未継承");
	// オブジェクト生成
	auto item = m_pGameObjectManager->CreateObject<T>();
	SetupItem(item, obj);

	return item;
}

template<class T>
inline void ItemObjectManager::CallItem(GameObject* obj)
{
	// 継承チェック
	static_assert(std::is_base_of<ItemObject, T>::value, "アイテム呼び出し:アイテムの基底クラスを未継承");
	// 再利用できるオブジェクトを探す
	for (auto& item : m_items) {
		// nullチェック
		if (!item)continue;
		// アクティブ状態でないオブジェクトを探す
		if (item->IsActive())continue;
		// 同じクラスかどうかチェック
		if (!dynamic_cast<T*>(m_items[0])) continue;
		//if (!std::is_same < T, typeid(item) > ::value)continue;
		// アイテムのセットアップ
		item->Setup(obj->GetTransform());

		return;
	}

	// 再利用できるオブジェクトがなければ
	auto item=CreateItem<T>(obj);
	//item->SetupItem(item, obj);

	return;
}
