#include"pch.h"
#include "ItemObjectManager.h"
#include "ItemObjectBase.h"
#include "../../GameObject.h"
#include"../../UI/ItemCursor.h"

ItemObjectManager::ItemObjectManager()
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
	printfDx("item active num : %d\n", m_items.size());
}

void ItemObjectManager::SetupItem(ItemObjectBase* item, GameObject* obj)
{
	item->Setup(obj->GetTransform());
}
