#include "ItemObjectManager.h"
#include "ItemObject.h"
#include "../../GameObject.h"
#include"../../UI/ItemCursor.h"

ItemObjectManager::ItemObjectManager():
	m_pGameObjectManager(nullptr)
{
	
}

ItemObjectManager::~ItemObjectManager()
{

}

void ItemObjectManager::Init()
{

}

void ItemObjectManager::End()
{

}

void ItemObjectManager::Update()
{

}

void ItemObjectManager::Draw()
{
	printfDx("m_items.size : %d\n", m_items.size());
}

void ItemObjectManager::SetupItem(ItemObject* item, GameObject* obj)
{
	item->Setup(obj->GetTransform());
}
