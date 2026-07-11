#include "ItemObjectManager.h"
#include "ItemObject.h"
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
}

void ItemObjectManager::SetupItem(ItemObject* item, GameObject* obj)
{
	item->Setup(obj->GetTransform());
}
