#include "MapCreate.h"
#include "MapManager.h"
#include "MapTile.h"
#include "MapConst.h"

#include"../../Utility/MyRandom.h"

#include<functional>

MapCreate& MapCreate::GetInstance()
{
	static MapCreate instance;
	return instance;
}

void MapCreate::CreateMap()
{
	// 最初のエリアを生成
	CreateFirstArea();
	// エリアを分割
	DivideAreaFixCount();
	// 部屋の配置

	// 全部屋を連結

	// 階段を置く
}

void MapCreate::CreateFirstArea()
{
	//void (*action)(MapTile*) = MapCreate::SetFirstWall;
	// 全てのマスを壁にする
	//std::function<void(MapTile*)> action = SetFirstWall;
	MapManager::GetInstance().SetFirstWall();
	AreaData* firstArea = new AreaData(2, 2, MAP_SQUARE_WIDTH_COUNT - 4, MAP_SQUARE_HEIGHT_COUNT - 4);
	m_areaData.push_back(firstArea);
}

void MapCreate::SetFirstWall(MapTile* tile)
{
	tile->SetTerrain(eTerrain::Wall);
	// 最初の分割線マスを追加
	int x = static_cast<int>(tile->GetPosX());
	int y = static_cast<int>(tile->GetPosY());
	// 外周マスの排除
	if (x == 0 || x == MAP_SQUARE_WIDTH_COUNT - 1 ||
		y == 0 || y == MAP_SQUARE_HEIGHT_COUNT - 1) return;
	// 外周から1マス離れたマス以外の排除
	if (x != 1 && x != MAP_SQUARE_WIDTH_COUNT - 2 &&
		y != 1 && y != MAP_SQUARE_HEIGHT_COUNT - 2) return;
	// 分割線マスの追加
	AddDivideLine(tile);
}



void MapCreate::AddDivideLine(MapTile* tile)
{
	m_divideLine.push_back(tile->GetId());
	tile->SetTerrain(eTerrain::Wall);
}

void MapCreate::DivideAreaFixCount()
{
	for (int i = 0; i < _AREA_DEVIDE_COUNT; i++) {
		// 幅最大のエリアを取得
		AreaData* devideArea = GetMaxSizeArea();
		bool isVertical = devideArea->sizeX < devideArea->sizeY;
		// 三項演算子：条件 ? trueの際の処理 : falseの際の処理 ;
		int maxSize = isVertical ? devideArea->sizeY : devideArea->sizeX;
		// 取得したエリアが分割可能か判定
		if (maxSize < (_MIN_ROOM_SIZE + 2) * 2 + 1) break;
		// 取得したエリアを分割
		DivideArea(devideArea, isVertical);
	}
}

void MapCreate::DivideArea(AreaData* divideArea, bool isVertical)
{
	if (isVertical) {
		// エリアを上下に分割
		DivideAreaVertical(divideArea);
	}
	else {
		// エリアを左右に分割
		DivideAreaHorizontal(divideArea);
	}
}

void MapCreate::DivideAreaVertical(AreaData* divideArea)
{
	// 分割位置の決定
	int randomMax = divideArea->sizeY - (_MIN_ROOM_SIZE + 2) * 2;
	int devidePos = MyRandom::Int(0, randomMax);
	devidePos += _MIN_ROOM_SIZE + 2 + divideArea->startY;
	// 新しいエリアを生成
	int newAreaHeight = divideArea->startY + divideArea->sizeY- devidePos - 1;
	int newAreaY = devidePos + 1;
	AreaData* newArea = new AreaData(divideArea->startX, newAreaY, divideArea->sizeX, newAreaHeight);
	m_areaData.push_back(newArea);
	// 既存エリアの修正
	divideArea->sizeY = devidePos - divideArea->startY;
	// 分割線マスの追加
	for (int x = 0; x < divideArea->sizeX; x++) {
		MapTile* square = MapManager::GetInstance().GetTile(divideArea->startX + x, devidePos);
		AddDivideLine(square);
	}
}

void MapCreate::DivideAreaHorizontal(AreaData* divideArea)
{
	// 分割位置の決定
	int randomMax = divideArea->sizeX - (_MIN_ROOM_SIZE + 2) * 2;
	int devidePos = MyRandom::Int(0, randomMax);
	devidePos += _MIN_ROOM_SIZE + 2 + divideArea->startX;
	// 新しいエリアを生成
	int newAreaWidth = divideArea->startX+ divideArea->sizeX - devidePos - 1;
	int newAreaX = devidePos + 1;
	AreaData* newArea = new AreaData(newAreaX, divideArea->startY, newAreaWidth, divideArea->sizeY);
	m_areaData.push_back(newArea);
	// 既存エリアの修正
	divideArea->sizeX = devidePos - divideArea->startX;
	// 分割線マスの追加
	for (int y = 0; y < divideArea->sizeY; y++) {
		MapTile* square = MapManager::GetInstance().GetTile(devidePos, divideArea->startY+ y);
		AddDivideLine(square);
	}
}

MapCreate::AreaData* MapCreate::GetMaxSizeArea()
{
	int maxSize = -1;
	AreaData* result=nullptr;
	for (int i = 0; i < m_areaData.size(); i++) {
		AreaData* area = m_areaData[i];
		// 横幅の確認
		if (area->sizeX > maxSize) {
			maxSize = area->sizeX;
			result = area;
		}
		// 縦幅の確認
		if (area->sizeY > maxSize) {
			maxSize = area->sizeY;
			result = area;
		}
	}
	return result;
}

void MapCreate::CreateAllRoom()
{
	for (int i = 0; i < m_areaData.size(); i++)
	{
		CreateRoom(m_areaData[i]);
	}
}

void MapCreate::CreateRoom(AreaData* area)
{
	if (!area) return;

	// 部屋のサイズ決定
	int roomWidth = MyRandom::Int(_MIN_ROOM_SIZE, area->sizeX - 2 + 1);
	int roomheight = MyRandom::Int(_MIN_ROOM_SIZE, area->sizeY - 2 + 1);
	// 部屋の位置決定
	int xRandomRange = area->sizeX - roomWidth;
	int yRandomRange = area->sizeY - roomheight;
	int startX = area->startX + MyRandom::Int(1, xRandomRange);
	int startY = area->startY + MyRandom::Int(1, yRandomRange);
	// 部屋の生成
	std::vector<int>;
	for (int y = 0; y < roomheight; y++)
	{
		for (int x = 0; x < roomWidth; x++)
		{
			MapTile* square = MapManager::GetInstance().GetTile(startX + x, startY + y);
			if (!square) continue;
			// マスを部屋地形に変更
			square->SetTerrain(eTerrain::Room);
			m_rooms.push_back(square.squareData.Id);
		}
	}
	MapManager::GetInstance().AddRoom(roomidList);
}
