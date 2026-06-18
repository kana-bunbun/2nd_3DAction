#include "MapDraw.h"
#include"MapConst.h"
#include"MapCreate.h"
#include"MapManager.h"
#include"TileObject.h"
#include"FloorTile.h"
#include"WallTile.h"
#include"../../Utility/Game.h"
#include"../../Utility/Color.h"
#include<DxLib.h>
#include<vector>

namespace {
	constexpr Vector3 blockSize = { 5.0f,5.0f,0.0f };
	constexpr Vector3 blockInterval = { blockSize.x,blockSize.y,0.0f };
	constexpr Vector3 kDrawBlockStart ={
		-(blockInterval.x* (static_cast<float>(MapConst::MAP_SQUARE_WIDTH_COUNT) * 0.5f) - (blockInterval.x * 0.5f) * (MapConst::MAP_SQUARE_WIDTH_COUNT % 2)),
		blockInterval.y* (static_cast<float>(MapConst::MAP_SQUARE_HEIGHT_COUNT) * 0.5f) - (blockInterval.y * 0.5f) * (MapConst::MAP_SQUARE_WIDTH_COUNT % 2),
		0.0f};
	constexpr Vector3 kDrawCenter = 
	{
		Game::kScreenWidth- blockSize.x*(MapConst::MAP_SQUARE_WIDTH_COUNT*0.5f+10),
		blockSize.y * (MapConst::MAP_SQUARE_HEIGHT_COUNT * 0.5f + 10),
		0.0f
	};
	constexpr Vector3 kDrawSize = { 250.0f,250.0f,0.0f };
	constexpr Vector3 kMapSize = { MapConst::kTileSize * MapConst::MAP_SQUARE_WIDTH_COUNT,MapConst::kTileSize  * MapConst::MAP_SQUARE_HEIGHT_COUNT,0.0f };
	const char* const kCursorPath = "Resource\\UI\\MapPlayerCursor.png";
	const char* const kWallPath = "Resource\\Map\\wall.mv1";
	const char* const kFloorPath = "Resource\\Map\\floor.mv1";
}

MapDraw::MapDraw():
	m_markPos(),
	m_cursorHandle(-1),
	m_pTiles()
{
	m_markPos.Reset();
	MapManager::GetInstance().Initialize();
	MapCreate::GetInstance().CreateMap();
	m_cursorHandle = LoadGraph(kCursorPath);
	m_pTiles.clear();

	m_wallHandle = MV1LoadModel(kWallPath);
	m_floorHandle = MV1LoadModel(kFloorPath);
	for (int i = 0; i < MapConst::MAP_SQUARE_HEIGHT_COUNT * MapConst::MAP_SQUARE_HEIGHT_COUNT; i++) {
		MapConst::eTerrain terrain = MapManager::GetInstance().GetTile(i)->GetSquareData()->GetTerrain();
		switch (terrain)
		{
		case MapConst::eTerrain::Passage:
		case MapConst::eTerrain::Room:
		{
			std::unique_ptr<FloorTile> floor = std::make_unique<FloorTile>(i, GetTilePosFromID(i));
			floor->SetFloorModel(MV1DuplicateModel(m_floorHandle));
			m_pTiles.push_back(std::move(floor));
			break;
		}
		case MapConst::eTerrain::Wall: {
			std::unique_ptr<WallTile> wall = std::make_unique<WallTile>(i, GetTilePosFromID(i));
			wall->SetWallHandle(MV1DuplicateModel(m_wallHandle));
			wall->SetFloorModel(MV1DuplicateModel(m_floorHandle));
			//wall->SetPillerHandle(m_pillerHandle);
			m_pTiles.push_back(std::move(wall));
			break;
		}
		case MapConst::eTerrain::Invalid:
		default:
			continue;
		}
	}
}

MapDraw::~MapDraw()
{
	DeleteGraph(m_cursorHandle);
	MV1DeleteModel(m_floorHandle);
	MV1DeleteModel(m_wallHandle);
}

void MapDraw::Draw()
{
	for (auto& tile : m_pTiles) {
		tile->Update(0);
		tile->Draw();

	}
	DrawMiniMap();
	DrawMark();
}

void MapDraw::DrawMap()
{
	Vector3 pos;

	for (int y = 0; y < MapConst::MAP_SQUARE_HEIGHT_COUNT; y++) {
		for (int x = 0; x < MapConst::MAP_SQUARE_WIDTH_COUNT; x++) {
			pos.x = x * MapConst::kTileSize  * 2;
			pos.y = -MapConst::kTileSize ;
			pos.z = y * MapConst::kTileSize  * 2;
			int color = Color::kWhite;
			MapConst::eTerrain terrain = MapManager::GetInstance().GetTile(MapManager::GetInstance().PositionToID(x, y))->GetSquareData()->GetTerrain();
			switch (terrain) {
			case::MapConst::eTerrain::Invalid:
				continue;
			case::MapConst::eTerrain::Passage:
				color = Color::kCyan;
				break;
			case::MapConst::eTerrain::Room:
				color = Color::kBlue;
				break;
			case::MapConst::eTerrain::Wall:
				color = Color::kRed;
				break;
			default:
				color = Color::kBlack;

				break;
			}
		
			DrawSphere3D(pos.ToVECTOR(), MapConst::kTileSize , 10, color, color, true);

		}
	}
}

void MapDraw::DrawMiniMap()
{

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawBox(drawCenter.x - (drawSize.x * 0.5f), drawCenter.y - (drawSize.y * 0.5f),
	//drawCenter.x + (drawSize.x * 0.5f), drawCenter.y + (drawSize.y * 0.5f),
	//0x000000, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int y = 0; y < MapConst::MAP_SQUARE_HEIGHT_COUNT; y++) {
		for (int x = 0; x < MapConst::MAP_SQUARE_WIDTH_COUNT; x++) {
			int color = Color::kBlack;
			MapConst::eTerrain terrain = MapManager::GetInstance().GetTile(MapManager::GetInstance().PositionToID(x, y))->GetSquareData()->GetTerrain();
			switch (terrain) {
			case::MapConst::eTerrain::Invalid:
				break;
			case::MapConst::eTerrain::Passage:
				color = Color::kCyan;
				break;
			case::MapConst::eTerrain::Room:
				color = Color::kBlue;
				break;
			case::MapConst::eTerrain::Wall:
				color = Color::kRed;
				break;
			default:
				color = Color::kBlack;
				break;
			}
	/*		if (InDevideList(MapManager::GetInstance().PositionToID(x, y))) {
				color = Color::kCyan;
			}*/
			int id = MapManager::GetInstance().PositionToID(x, y);

			Vector3 drawBox = kDrawCenter + Vector3(-blockInterval.x * x, blockInterval.y * y, 0.0f) - kDrawBlockStart;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(drawBox.x - (blockSize.x * 0.5f), drawBox.y - (blockSize.y * 0.5f),
				drawBox.x + (blockSize.x * 0.5f), drawBox.y + (blockSize.y * 0.5f),
				color, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
	}

}

bool MapDraw::InDevideList(size_t id)
{
	std::vector<int >devideLine = MapCreate::GetInstance().GetDivideLine();
	for (int i = 0; i < devideLine.size(); i++) {
		if (devideLine[i] == id)return true;
	}
	return false;
}

void MapDraw::DrawMark()
{
	Vector3 drawStart = kDrawCenter - kDrawBlockStart;
	Vector3 toMapPos=Vector3::zero;
	toMapPos.x= m_markPos.position.x / kMapSize.x* kDrawBlockStart.x;
	toMapPos.y= m_markPos.position.z / kMapSize.y* kDrawBlockStart.y;
	toMapPos += drawStart;
	DrawRotaGraph(toMapPos.x, toMapPos.y, 0.20f, m_markPos.rotation.y, m_cursorHandle, TRUE);
}

Vector3 MapDraw::GetTilePosFromID(int ID)
{
	int initPosX = MapManager::GetInstance().IDToPosX(ID);
	int initPosZ = MapManager::GetInstance().IDToPosY(ID);
	Vector3 pos(initPosX, 0, initPosZ);
	return pos * MapConst::kTileSize *2;
}
