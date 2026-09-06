#include"pch.h"
#include "Character.h"

const std::function<void(const ItemData::Type&, int)>& Character::GetAddItem()
{
    return [this](const ItemData::Type& type, int add) {m_itemList->AddItem(type, add); };
}

const std::function<void(int, int)>& Character::GetSubItem()
{
    return [this](int slotID, int add) {m_itemList->UseItem(slotID, add); };
}
