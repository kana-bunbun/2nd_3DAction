#pragma once
#include"../../GameObjectManager.h"
#include<vector>
#include<memory>
#include<type_traits>
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
	T* CreateItem();
	// アイテム呼び出し
	template<class T>
	void CallItem();
	void SetupItem(ItemObject* item, GameObject* obj);

	template<class T1,class T2>
	bool CheckClass(T1* class1, T2 class2);
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
inline T* ItemObjectManager::CreateItem()
{
	// 継承チェック
	static_assert(std::is_base_of<ItemObject, T>::value, "アイテム生成:アイテムの基底クラスを未継承");
	// オブジェクト生成
	auto item = m_pGameObjectManager->CreateObject<T>();
	return item;
}

template<class T>
inline void ItemObjectManager::CallItem()
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
		if (!std::is_same(T,std::type_identity_v))continue;
		// アイテムのセットアップ
		item->Setup();
		return;
	}

	// 再利用できるオブジェクトがなければ
	CreateItem<T>();

	return;
}

template<class T1, class T2>
inline bool ItemObjectManager::CheckClass(T1* class1, T2 class2)
{

	return std::is_same<T1,T2>::value;
}
