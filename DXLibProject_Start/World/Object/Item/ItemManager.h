#pragma once
#include<memory>
class ItemObjectManager;
class ItemManager
{
public:
	ItemManager();
	~ItemManager();
	
	void Init();
	void End();
	void Update();
	void Draw();


public:
	ItemCursor* GetItemCursor() { return m_pItemCursor.get(); }
private:
	std::unique_ptr<ItemObjectManager>m_pItemObjectManager;
	// アイテムカーソル
	std::unique_ptr<ItemCursor> m_pItemCursor;
};

