#pragma once
#include<memory>
class ItemObjectManager;
class Player;
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
	void SetGameObjectManager(GameObjectManager* pGameObjectManager);
	ItemCursor* GetItemCursor() { return m_pItemCursor.get(); }
	void SetPlayer(Player* pPlayer);
private:
	GameObjectManager* m_pGameObjectManager;
	std::unique_ptr<ItemObjectManager>m_pItemObjectManager;
	// アイテムカーソル
	std::unique_ptr<ItemCursor> m_pItemCursor;
	Player* player;
};

