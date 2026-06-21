#include "MapManager.h"
#include"MapTile.h"
#include"MapConst.h"

#include<functional>

MapManager& MapManager::GetInstance()
{
    static MapManager instance;
    return instance;
}


void MapManager::Initialize()
{
    // 部屋情報を初期化
    ResetRoomData();
    // マスが生成されていたら処理しない
    if (!m_mapData.empty())return;
    // マスオブジェクトを必要数生成
    int squareCount = MapConst::MAP_SQUARE_HEIGHT_COUNT * MapConst::MAP_SQUARE_WIDTH_COUNT;
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
    if (posX < 0 || posX >= MapConst::MAP_SQUARE_WIDTH_COUNT ||
        posY < 0 || posY >= MapConst::MAP_SQUARE_HEIGHT_COUNT) return -1;
    return posY * MapConst::MAP_SQUARE_WIDTH_COUNT + posX;
}

int MapManager::IDToPosX(size_t ID)
{
    int positionX = -1;
    if (ID >= MapConst::MAP_SQUARE_HEIGHT_COUNT * MapConst::MAP_SQUARE_WIDTH_COUNT)return -1;


    positionX = ID % MapConst::MAP_SQUARE_WIDTH_COUNT;
    return positionX;
}

int MapManager::IDToPosY(size_t ID)
{
    int positionY=-1;
    if (ID >= MapConst::MAP_SQUARE_HEIGHT_COUNT * MapConst::MAP_SQUARE_WIDTH_COUNT)return -1;


    positionY = ID / MapConst::MAP_SQUARE_WIDTH_COUNT;
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

MapTile* MapManager::GetToDirSquare(int x, int y, MapConst::eDirectionFour direction)
{
    int beforeX = x, beforeY = y;
    // 指定方向の隣接マス取得
    ToDirPosition(x, y, direction);
    // ブレークポインタを置いて確認する可能性を考慮して一時格納
    MapTile* result = GetTile(x, y);
    return result;
}
MapTile* MapManager::GetToDirSquare(int ID, MapConst::eDirectionFour direction)
{
    int beforeX = IDToPosX(ID), beforeY = IDToPosY(ID);
    return GetToDirSquare(beforeX,beforeY,direction);
}

void MapManager::ToDirPosition(int& x, int& y, MapConst::eDirectionFour direction)
{
    switch (direction)
    {
    case MapConst::eDirectionFour::Invalid:
        break;
    case MapConst::eDirectionFour::Up:
        y++;
        break;
    case MapConst::eDirectionFour::Right:
        x++;
        break;
    case MapConst::eDirectionFour::Down:
        y--;
        break;
    case MapConst::eDirectionFour::Left:
        x--;
        break;
    case MapConst::eDirectionFour::Max:
        break;
    default:
        break;
    }
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

void MapManager::ResetRoomData()
{
    // 部屋情報の初期化
    m_rooms.clear();
    m_unUseRooms.clear();
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

void MapManager::SetInvalid()
{
    int id;
    std::vector<MapTile*>openTile;
    for (int i = 0; i < m_mapData.size(); i++) {
        id = m_mapData[i]->GetId();
        std::vector<int>chebyshevList = CheckChebyshevID(id);
        bool isWall = true;
        for (int& chebyshevID : chebyshevList) {
            MapTile* tile = GetTile(chebyshevID);
            if (tile && tile->GetSquareData()->GetTerrain() != MapConst::eTerrain::Wall) {
            isWall = false;
            break;
            }
        }
        if(isWall)
        openTile.push_back(GetTile(id));
    }
    for(auto& checkTile:openTile)
        checkTile->SetTerrain(MapConst::eTerrain::Invalid);
}

Vector3 MapManager::GetWorldPosFromID(int ID)
{
    int initPosX = IDToPosX(ID);
    int initPosZ = IDToPosY(ID);
    Vector3 pos(initPosX, 0, initPosZ);
    return pos * MapConst::kTileSize * 2;
}

int MapManager::GetIDFromWorldPos(Vector3 position)
{
    int posX = (position.x + MapConst::kTileSize) / (MapConst::kTileSize * 2);
    int posZ = (position.z + MapConst::kTileSize) / (MapConst::kTileSize * 2);
    return PositionToID(posX, posZ);
}

std::vector<int> MapManager::CheckChebyshevID(int centerID)
{
    std::vector<int>result;

    for (int i = 0; i < static_cast<int>(MapConst::eDirectionFour::Max); i++) {
        // 方向のキャッシュ
        MapConst::eDirectionEight direction = static_cast<MapConst::eDirectionEight>(i);
        // 指定方向マスのIDを取得
        int ID = DirectionToPosition(centerID, direction);
        if (ID == -1)continue;
        // マスIDが不正値でないとき配列に追加
        result.push_back(ID);
    }

    return result;

}

int MapManager::DirectionToPosition(int ID, MapConst::eDirectionEight direction)
{
    int result=-1;
    int centerX = IDToPosX(ID);
    int centerY = IDToPosY(ID);
    switch (direction)
    {
    case MapConst::eDirectionEight::Up:
        centerY++;
        break;
    case MapConst::eDirectionEight::UpRight:
        centerX++;
        centerY++;
        break;
    case MapConst::eDirectionEight::Right:
        centerX++;
        break;
    case MapConst::eDirectionEight::DownRight:
        centerX++;
        centerY--;
        break;
    case MapConst::eDirectionEight::Down:
        centerY--;
        break;
    case MapConst::eDirectionEight::DownLeft:
        centerX--;
        centerY--;
        break;
    case MapConst::eDirectionEight::Left:
        centerX--;
        break;
    case MapConst::eDirectionEight::UpLeft:
        centerX--;
        centerY++;
        break;
    case MapConst::eDirectionEight::Invalid:
    case MapConst::eDirectionEight::Max:
    default:
        break;
    }
    result = PositionToID(centerX, centerY);
    return result;
}
