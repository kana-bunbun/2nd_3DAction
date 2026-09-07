#include"pch.h"
#include "ItemData.h"

void ItemData::Sub(int subVallue)
{
    m_num -= subVallue;
    if (m_num > 0)return;
    m_num = 0;
    m_type = Type::Invalid;
}
bool ItemData::ExistItem()
{
    if (m_num <= 0 ||
        m_type == ItemData::Type::Invalid)return false;
    return true;
}
