#include "TileManager.h"
#include"MapConst.h"
#include"MapCreate.h"
#include"MapManager.h"
#include"TileObject.h"
#include"FloorTile.h"
#include"WallTile.h"
#include"../../Utility/Game.h"
#include"../../Utility/Color.h"
#include"../../Utility/MyRandom.h"
#include"../Object/Stair.h"
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

TileManager::TileManager():
	m_markPos(),
	m_cursorHandle(-1),
	m_pTiles(),
	stair(nullptr)
{
	
	m_markPos.Reset();
	m_pTiles.clear();
	MapManager::GetInstance().Initialize();
	
	MapCreate::GetInstance().CreateMap();
	
	m_cursorHandle = LoadGraph(kCursorPath);

	m_wallHandle = MV1LoadModel(kWallPath);
	m_floorHandle = MV1LoadModel(kFloorPath);
	for (int i = 0; i < MapConst::MAP_SQUARE_HEIGHT_COUNT * MapConst::MAP_SQUARE_HEIGHT_COUNT; i++) {
		MapConst::eTerrain terrain = MapManager::GetInstance().GetTile(i)->GetSquareData()->GetTerrain();
		switch (terrain)
		{
		case MapConst::eTerrain::Passage:
		case MapConst::eTerrain::Room:
		{
			std::unique_ptr<FloorTile> floor = std::make_unique<FloorTile>(i, MapManager::GetInstance().GetWorldPosFromID(i));
			floor->SetFloorModel(MV1DuplicateModel(m_floorHandle));
			m_pTiles.push_back(std::move(floor));
			break;
		}
		case MapConst::eTerrain::Wall: {
			std::unique_ptr<WallTile> wall = std::make_unique<WallTile>(i, MapManager::GetInstance().GetWorldPosFromID(i));
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
	stair = std::make_unique<Stair>();
	stair->SetTile(RandomRoomID());
}

TileManager::~TileManager()
{
	DeleteGraph(m_cursorHandle);
	MV1DeleteModel(m_floorHandle);
	MV1DeleteModel(m_wallHandle);
}

void TileManager::Draw()
{
	// マップの描画処理
	for (auto& tile : m_pTiles) {
		tile->Draw();
	}
	if (stair) {
		stair->Update(0);
	}

	// デバッグでプレイヤーのいるマスを取得・描画=====
	int id=MapManager::GetInstance().GetIDFromWorldPos(m_markPos.position);
	Vector3 pos= MapManager::GetInstance().GetWorldPosFromID(id);
	DrawSphere3D(pos.ToVECTOR(), 30, 10, 0xff00ff, 0xff00ff, TRUE);
	// =================================================

	// ミニマップ描画
	DrawMiniMap();
	// ミニマップ上のプレイヤー位置の描画
	DrawMark();
}


void TileManager::DrawMiniMap()
{

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

bool TileManager::InDevideList(size_t id)
{
	std::vector<int >devideLine = MapCreate::GetInstance().GetDivideLine();
	for (int i = 0; i < devideLine.size(); i++) {
		if (devideLine[i] == id)return true;
	}
	return false;
}

void TileManager::DrawMark()
{
	Vector3 drawStart = kDrawCenter - kDrawBlockStart;
	Vector3 toMapPos=Vector3::zero;
	toMapPos.x= m_markPos.position.x / kMapSize.x* kDrawBlockStart.x;
	toMapPos.y= m_markPos.position.z / kMapSize.y* kDrawBlockStart.y;
	toMapPos += drawStart;
	DrawRotaGraph(toMapPos.x, toMapPos.y, 0.20f, m_markPos.rotation.y, m_cursorHandle, TRUE);
}

int TileManager::RandomPassableID()
{
	std::vector<int> passableID = MapCreate::GetInstance().GetPassable();
	int random = MyRandom::Int(0, passableID.size() - 1);
	return passableID[random];
}

int TileManager::RandomRoomID()
{
	std::vector<int> roomID = MapCreate::GetInstance().GetRooms();
	int random = MyRandom::Int(0, roomID.size() - 1);
	return roomID[random];
}
