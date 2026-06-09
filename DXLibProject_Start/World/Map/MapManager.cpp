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
        int generatePosX = IDToPosX(i);
        int generatePosY = IDToPosY(i);
        // オブジェクト生成
        m_mapData.emplace_back(std::make_unique<MapTile>(generatePosX,generatePosY,i));
    }
}

int MapManager::PositionToID(int posX,int posY)
{
    // マップの範囲外を指定していたら不正な値を返す
    if (posX < 0 || posX >= MAP_SQUARE_WIDTH_COUNT ||
        posY < 0 || posY >= MAP_SQUARE_HEIGHT_COUNT) return -1;
    return posY * MAP_SQUARE_WIDTH_COUNT + posX;
}

int MapManager::IDToPosX(size_t ID)
{
    int positionX = -1;
    if (ID >= MAP_SQUARE_HEIGHT_COUNT * MAP_SQUARE_WIDTH_COUNT)return -1;


    positionX = ID % MAP_SQUARE_WIDTH_COUNT;
    return positionX;
}

int MapManager::IDToPosY(size_t ID)
{
    int positionY=-1;
    if (ID >= MAP_SQUARE_HEIGHT_COUNT * MAP_SQUARE_WIDTH_COUNT)return -1;


    positionY = ID / MAP_SQUARE_WIDTH_COUNT;
    return positionY;
}

MapTile* MapManager::GetTile(int ID)
{
    if(ID<0||
        ID >= m_mapData.size())return nullptr;

    return m_mapData[ID].get();
}

MapTile* MapManager::GetTile(int posX,int posY)
{
    return GetTile(PositionToID(posX,posY));
}

void MapManager::ExecuteAllSquare(std::function<void(MapTile*)>& action)
{
    if (!action || m_mapData.empty()) return;
    for (int i = 0; i < m_mapData.size(); i++) {
        action(m_mapData[i].get());
    }
}

void MapManager::AddRoom(std::vector<int> idList)
{
    //std::unique_ptr<RoomData> addRoom = GetCanUseRoom();
    int addId = m_rooms.size();
    m_rooms.emplace_back(GetCanUseRoom());
    m_rooms[m_rooms.size() - 1]->SetUp(addId, idList);
}


RoomData* MapManager::GetCanUseRoom()
{
    // 未使用のものがなければインスタンスを生成
      // 配列に何もなければ未使用がない
    if (m_unUseRooms.empty()) return new RoomData();
    RoomData* result = m_unUseRooms[0].get();
    m_unUseRooms.erase(m_unUseRooms.begin());
    // 未使用のものがあればそれを返す
    return result;

    return nullptr;
}

void MapManager::RemoveAllRoom()
{
    if (m_rooms.empty()) return;
    for (int i = 0; i < m_rooms.size(); i++)
    {
        RoomData* roomData = m_rooms[i].get();
        if (!roomData) continue;

        roomData->Teardown();
        m_unUseRooms.clear();

    }
}

void MapManager::SetFirstWall()
{
    for (int i = 0; i < m_mapData.size(); i++) {
        m_mapData[i]->SetTerrain(eTerrain::Wall);
        // 最初の分割線マスを追加
        int x = static_cast<int>(m_mapData[i]->GetPosX());
        int y = static_cast<int>(m_mapData[i]->GetPosY());
        // 外周マスの排除
        if (x == 0 || x == MAP_SQUARE_WIDTH_COUNT - 1 ||
            y == 0 || y == MAP_SQUARE_HEIGHT_COUNT - 1) continue;
        // 外周から1マス離れたマス以外の排除
        if (x != 1 && x != MAP_SQUARE_WIDTH_COUNT - 2 &&
            y != 1 && y != MAP_SQUARE_HEIGHT_COUNT - 2) continue;
        // 分割線マスの追加
        MapCreate::GetInstance().AddDivideLine(m_mapData[i].get());
    }
}

void MapManager::SetInvalid()
{
    int id;
    std::vector<MapTile*>openTile;
    for (int i = 0; i < m_mapData.size(); i++) {
        id = m_mapData[i]->GetId();
        MapTile* checkTile = GetTile(id + 1);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        checkTile = GetTile(id - 1);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        checkTile = GetTile(id + MAP_SQUARE_WIDTH_COUNT);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        checkTile = GetTile(id - MAP_SQUARE_WIDTH_COUNT);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        checkTile = GetTile(id + MAP_SQUARE_WIDTH_COUNT-1);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        checkTile = GetTile(id + MAP_SQUARE_WIDTH_COUNT+1);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        checkTile = GetTile(id - MAP_SQUARE_WIDTH_COUNT-1);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        checkTile = GetTile(id - MAP_SQUARE_WIDTH_COUNT+1);
        if (checkTile && checkTile->GetSquareData()->GetTerrain() != eTerrain::Wall)continue;
        openTile.push_back(GetTile(id));
    }
    for(auto& checkTile:openTile)
        checkTile->SetTerrain(eTerrain::Invalid);
}
