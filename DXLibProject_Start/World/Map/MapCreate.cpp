#include "MapCreate.h"
#include "MapManager.h"
#include "MapTile.h"
#include "MapConst.h"
#include "ManhattanMoveData.h"

#include"../../Utility/MyRandom.h"
#include"ExpantionMethod.h"
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
	CreateAllRoom();

	// 全部屋を連結

	// 階段を置く

	MapManager::GetInstance().SetInvalid();

}

void MapCreate::CreateFirstArea()
{
	//void (*action)(MapTile*) = MapCreate::SetFirstWall;
	// 全てのマスを壁にする
	//std::function<void(MapTile*)> action = SetFirstWall;
	MapManager::GetInstance().SetFirstWall();
	AreaData* firstArea = new AreaData(2, 2, MapConst::MAP_SQUARE_WIDTH_COUNT - 4, MapConst::MAP_SQUARE_HEIGHT_COUNT - 4);
	m_areas.push_back(firstArea);
}

void MapCreate::SetFirstWall(MapTile* tile)
{
	tile->SetTerrain(MapConst::eTerrain::Wall);
	// 最初の分割線マスを追加
	int x = static_cast<int>(tile->GetPosX());
	int y = static_cast<int>(tile->GetPosY());
	// 外周マスの排除
	if (x == 0 || x == MapConst::MAP_SQUARE_WIDTH_COUNT - 1 ||
		y == 0 || y == MapConst::MAP_SQUARE_HEIGHT_COUNT - 1) return;
	// 外周から1マス離れたマス以外の排除
	if (x != 1 && x != MapConst::MAP_SQUARE_WIDTH_COUNT - 2 &&
		y != 1 && y != MapConst::MAP_SQUARE_HEIGHT_COUNT - 2) return;
	// 分割線マスの追加
	AddDivideLine(tile);
}



void MapCreate::AddDivideLine(MapTile* tile)
{
	m_divideLines.push_back(tile->GetId());
	tile->SetTerrain(MapConst::eTerrain::Wall);
}

void MapCreate::DivideAreaFixCount()
{
	int divedeCount = MyRandom::Int(MapConst::AREA_DIVIDE_MIN, MapConst::AREA_DIVIDE_MAX);
	for (int i = 0; i < divedeCount; i++) {
		// 幅最大のエリアを取得
		AreaData* devideArea = GetMaxSizeArea();
		bool isVertical = devideArea->sizeX < devideArea->sizeY;
		// 三項演算子：条件 ? trueの際の処理 : falseの際の処理 ;
		int maxSize = isVertical ? devideArea->sizeY : devideArea->sizeX;
		// 取得したエリアが分割可能か判定
		if (maxSize < (MapConst::_MIN_ROOM_SIZE + 2) * 2 + 1) break;
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
	int randomMax = divideArea->sizeY - (MapConst::_MIN_ROOM_SIZE + 2) * 2;
	int devidePos = MyRandom::Int(0, randomMax-1);
	devidePos += MapConst::_MIN_ROOM_SIZE + 2 + divideArea->startY;
	// 新しいエリアを生成
	int newAreaHeight = divideArea->startY + divideArea->sizeY- devidePos - 1;
	int newAreaY = devidePos + 1;
	AreaData* newArea = new AreaData(divideArea->startX, newAreaY, divideArea->sizeX, newAreaHeight);
	m_areas.push_back(newArea);
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
	int randomMax = divideArea->sizeX - (MapConst::_MIN_ROOM_SIZE + 2) * 2;
	int devidePos = MyRandom::Int(0, randomMax-1);
	devidePos += MapConst::_MIN_ROOM_SIZE + 2 + divideArea->startX;
	// 新しいエリアを生成
	int newAreaWidth = divideArea->startX+ divideArea->sizeX - devidePos - 1;
	int newAreaX = devidePos + 1;
	AreaData* newArea = new AreaData(newAreaX, divideArea->startY, newAreaWidth, divideArea->sizeY);
	m_areas.push_back(newArea);
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
	for (int i = 0; i < m_areas.size(); i++) {
		AreaData* area = m_areas[i];
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
	for (int i = 0; i < m_areas.size(); i++)
	{
		CreateRoom(m_areas[i]);
	}
}

void MapCreate::CreateRoom(AreaData* area)
{
	if (!area) return;

	// 部屋のサイズ決定
	int roomWidth = MyRandom::Int(MapConst::_MIN_ROOM_SIZE, area->sizeX - 2);
	int roomheight = MyRandom::Int(MapConst::_MIN_ROOM_SIZE, area->sizeY - 2);
	// 部屋の位置決定
	int xRandomRange = area->sizeX - roomWidth;
	int yRandomRange = area->sizeY - roomheight;
	int startX = area->startX + MyRandom::Int(1, xRandomRange-1);
	int startY = area->startY + MyRandom::Int(1, yRandomRange-1);
	// 部屋の生成
	std::vector<int>rooms;
	for (int y = 0; y < roomheight; y++)
	{
		for (int x = 0; x < roomWidth; x++)
		{
			MapTile* square = MapManager::GetInstance().GetTile(startX + x, startY + y);
			if (!square) continue;
			// マスを部屋地形に変更
			square->SetTerrain(MapConst::eTerrain::Room);
			rooms.push_back(square->GetSquareData()->GetID());
		}
	}
	MapManager::GetInstance().AddRoom(rooms);
}

void MapCreate::ConnectAllRoom()
{
	// ランダムで使うため 1引いた値
	int directionMax = static_cast<int>(MapConst::eDirectionFour::Max) - 1;
	// ランダムに掘削方向を決定
	MapConst::eDirectionFour digDirection = static_cast<MapConst::eDirectionFour>(MyRandom::Int(0, directionMax));
	// 配列の番号を扱うためループカウンタを使った繰り返し
	for (int i = 0; i < m_areas.size()-1; i++) {
		// エリアから分割線まで掘削
		AreaData* area1 = m_areas[i];
		int startID = DigToDivideLine(area1, digDirection);
		// エリアから分割線まで掘削
		AreaData* area2 = m_areas[i+1];
		int goalID = DigToDivideLine(area2, digDirection);

		// 分割線内で通路をつなげる
		ConnectDivideLine(startID, goalID);

		// 掘削方向をランダムで決定
		int digIndex = static_cast<int>(digDirection) + MyRandom::Int(1, directionMax);
		if (digIndex >= static_cast<int>(MapConst::eDirectionFour::Max)) digIndex -= static_cast<int>(MapConst::eDirectionFour::Max);
		// eDirectionFourにキャスト
		digDirection = static_cast<MapConst::eDirectionFour>(digIndex);
	}
}

int MapCreate::DigToDivideLine(AreaData* area, MapConst::eDirectionFour direction)
{
	// 掘削方向の反対側が部屋マスなら掘削可能
	MapConst::eDirectionFour reverse = ExpantionMethod::ReverseRirection(direction);
	std::vector<MapTile*>targets;

	// areaへのアクセス回数を減らすためキャッシュ
	int startX = area->startX;
	int startY = area->startY;
	for (int y = 0; y < area->sizeY; y++) {
		for (int x = 0; x < area->sizeX; x++) {
			int squareX = startX + x;
			int squareY = startY + y;

			MapTile* tile = MapManager::GetInstance().GetTile(squareX, squareY);
			// 壁でなければ処理しない
			if (!tile || tile->GetSquareData()->GetTerrain() != MapConst::eTerrain::Wall) continue;
			// 走査
			MapTile* dirTile = MapManager::GetInstance().GetToDirSquare(squareX, squareY, reverse);
			if (!dirTile || dirTile->GetSquareData()->GetTerrain() != MapConst::eTerrain::Room) continue;
			targets.push_back(tile);

		}
	}
	// 要素がなければreturn
	if (targets.size() < 1)return -1;
	// ランダムに1マス抽選
	MapTile* currentTile = targets[MyRandom::Int(0, targets.size() - 1)];

	// 分割線にたどり着くまでループ
	while (true) {
		// currenTileを通路マスに
		currentTile->SetTerrain(MapConst::eTerrain::Passage);
		// 分割線までたどり着いたらループを抜ける
		if (std::find(m_divideLines.begin(), m_divideLines.end(), currentTile->GetSquareData()->GetID()) != m_divideLines.end());
		currentTile = MapManager::GetInstance().GetToDirSquare(currentTile->GetSquareData()->GetPosX(), currentTile->GetSquareData()->GetPosY(), direction);
	}

	return currentTile->GetSquareData()->GetID();
}

void MapCreate::ConnectDivideLine(int sartId, int goalLine)
{
	//std::vector<ManhattanMoveData> route=
}
