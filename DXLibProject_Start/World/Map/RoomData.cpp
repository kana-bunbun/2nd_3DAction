#include "RoomData.h"
#include "SquareData.h"
#include "MapTile.h"
#include "MapManager.h"

void RoomData::SetUp(int id, std::vector<int> idList)
{
    m_id = id;
    m_idList = idList;
    SetRoomIdAll(id);
}


void RoomData::Teardown()
{
    m_id = -1;

    SetRoomIdAll(m_id);
}

void RoomData::SetRoomIdAll(int Id)
{
    if (m_idList.empty()) return;
    for (int i = 0; i < m_idList.size(); i++)
    {
        MapTile* square = MapManager::GetInstance().GetTile(m_idList[i]);
        if (!square) continue;
        square->SetRoomId(Id);
    }
}
