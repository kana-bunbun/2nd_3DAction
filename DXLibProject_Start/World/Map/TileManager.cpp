#include "TileManager.h"
#include"MapConst.h"
#include"MapCreate.h"
#include"MapManager.h"
#include"TileObject.h"
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
	m_cursorHandle = LoadGraph(kCursorPath);

	m_wallHandle = MV1LoadModel(kWallPath);
	m_floorHandle = MV1LoadModel(kFloorPath);
	stair = std::make_unique<Stair>();
	SetUpFloor();
}

TileManager::~TileManager()
{
	DeleteGraph(m_cursorHandle);
	MV1DeleteModel(m_floorHandle);
	MV1DeleteModel(m_wallHandle);
}

void TileManager::SetUpFloor()
{
	// 部屋情報の初期化
	MapManager::GetInstance().Initialize();
	// マップ生成
	MapCreate::GetInstance().CreateMap();

	// 
	for (int i = 0; i < MapConst::MAP_SQUARE_HEIGHT_COUNT * MapConst::MAP_SQUARE_HEIGHT_COUNT; i++) {
		// タイルの種類によって分岐
		MapConst::eTerrain terrain = MapManager::GetInstance().GetTile(i)->GetSquareData()->GetTerrain();
		switch (terrain)
		{
		case MapConst::eTerrain::Passage:
		case MapConst::eTerrain::Room:
		case MapConst::eTerrain::Wall: 
		case MapConst::eTerrain::Invalid:
		{
			// 生成されていなければ
			if (i>=m_pTiles.size()) {
			// タイルを生成
			std::unique_ptr<TileObject> tile = std::make_unique<TileObject>(i, MapManager::GetInstance().GetWorldPosFromID(i), terrain);
			// モデルハンドルを設定
			tile->SetFloorModel(MV1DuplicateModel(m_floorHandle));
			tile->SetWallHandle(MV1DuplicateModel(m_wallHandle));
			// 配列に追加
			m_pTiles.push_back(std::move(tile));
			}
			// タイルが生成されていたら
			else {
				// タイル情報の変更をする
				m_pTiles[i]->ChangeTile(i, MapManager::GetInstance().GetWorldPosFromID(i), terrain);
			}
			break;
		}
		default:
			continue;
		}
	}
	stair->SetTile(RandomRoomID());
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
