#include "MapManager.h"
#include"MapTile.h"
#include"MapCreate.h"

#include<functional>

MapManager& MapManager::GetInstance()
{
    static MapManager instance;
    return instance;
}


void MapManager::Initialize()
{
    // マスオブジェクトを必要数生成
    int squareCount = MAP_SQUARE_HEIGHT_COUNT * MAP_SQUARE_WIDTH_COUNT;
    /*_squareList = new List<SquareObject>(squareCount);*/
    for (int i = 0; i < squareCount; i++) {
        Vector3 generatePos = IDToPosition(i);
        // オブジェクト生成
        m_mapData.emplace_back(std::make_unique<MapTile>(generatePos,i));
    }
}

int MapManager::PositionToID(Vector3 position)
{
    // マップの範囲外を指定していたら不正な値を返す
    if (position.x < 0 || position.x >= MAP_SQUARE_WIDTH_COUNT ||
        position.y < 0 || position.y >= MAP_SQUARE_HEIGHT_COUNT) return -1;
    return position.y * MAP_SQUARE_WIDTH_COUNT + position.x;
}

Vector3 MapManager::IDToPosition(size_t ID)
{
    Vector3 position=Vector3::zero;
    if (ID >= m_mapData.size())return Vector3(-1.0f, -1.0f, -1.0f);


    position.x = ID % MAP_SQUARE_WIDTH_COUNT;
    position.y = ID / MAP_SQUARE_WIDTH_COUNT;
    return position;
}

MapTile* MapManager::GetTile(size_t ID)
{
    if (ID >= m_mapData.size())return nullptr;

    return m_mapData[ID].get();
}

MapTile* MapManager::GetTile(Vector3 position)
{
    return GetTile(PositionToID(position));
}

void MapManager::ExecuteAllSquare(std::function<void(MapTile*)> action)
{
    if (!action || m_mapData.empty()) return;
    for (int i = 0; i < m_mapData.size(); i++) {
        action(m_mapData[i].get());
    }
}
