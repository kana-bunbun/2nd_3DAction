#include "ItemData.h"

bool ItemData::ExistItem()
{
    if (m_num <= 0 ||
        m_type == ItemData::Type::Invalid)return false;
    return true;
}
