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
	DevideAreaFixCount();
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
	int x = static_cast<int>(tile->GetPos().x);
	int y = static_cast<int>(tile->GetPos().y);
	// 外周マスの排除
	if (x == 0 || x == MAP_SQUARE_WIDTH_COUNT - 1 ||
		y == 0 || y == MAP_SQUARE_HEIGHT_COUNT - 1) return;
	// 外周から1マス離れたマス以外の排除
	if (x != 1 && x != MAP_SQUARE_WIDTH_COUNT - 2 &&
		y != 1 && y != MAP_SQUARE_HEIGHT_COUNT - 2) return;
	// 分割線マスの追加
	AddDevideLine(tile);
}



void MapCreate::AddDevideLine(MapTile* tile)
{
	m_devideLine.push_back(tile->GetId());
	tile->SetTerrain(eTerrain::Wall);
}

void MapCreate::DevideAreaFixCount()
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
		DevideArea(devideArea, isVertical);
	}
}

void MapCreate::DevideArea(AreaData* devideArea, bool isVertical)
{
	if (isVertical) {
		// エリアを上下に分割
		DevideAreaVertical(devideArea);
	}
	else {
		// エリアを左右に分割
		DevideAreaHorizontal(devideArea);
	}
}

void MapCreate::DevideAreaVertical(AreaData* devideArea)
{
	// 分割位置の決定
	int randomMax = devideArea->sizeY - (_MIN_ROOM_SIZE + 2) * 2;
	int devidePos = MyRandom::Int(0, randomMax);
	devidePos += _MIN_ROOM_SIZE + 2 + devideArea->startY;
	// 新しいエリアを生成
	int newAreaHeight = devideArea->startY + devideArea->sizeY- devidePos - 1;
	int newAreaY = devidePos + 1;
	AreaData* newArea = new AreaData(devideArea->startX, newAreaY, devideArea->sizeX, newAreaHeight);
	m_areaData.push_back(newArea);
	// 既存エリアの修正
	devideArea->sizeY = devidePos - devideArea->startY;
	// 分割線マスの追加
	for (int x = 0; x < devideArea->sizeX; x++) {
		MapTile* square = MapManager::GetInstance().GetTile(Vector3(devideArea->startX + x, devidePos,0));
		AddDevideLine(square);
	}
}

void MapCreate::DevideAreaHorizontal(AreaData* devideArea)
{
	// 分割位置の決定
	int randomMax = devideArea->sizeX - (_MIN_ROOM_SIZE + 2) * 2;
	int devidePos = MyRandom::Int(0, randomMax);
	devidePos += _MIN_ROOM_SIZE + 2 + devideArea->startX;
	// 新しいエリアを生成
	int newAreaWidth = devideArea->startX+ devideArea->sizeX - devidePos - 1;
	int newAreaX = devidePos + 1;
	AreaData* newArea = new AreaData(newAreaX, devideArea->startY, newAreaWidth, devideArea->sizeY);
	m_areaData.push_back(newArea);
	// 既存エリアの修正
	devideArea->sizeX = devidePos - devideArea->startX;
	// 分割線マスの追加
	for (int y = 0; y < devideArea->sizeY; y++) {
		MapTile* square = MapManager::GetInstance().GetTile(Vector3(devidePos, devideArea->startY+ y,0));
		AddDevideLine(square);
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
