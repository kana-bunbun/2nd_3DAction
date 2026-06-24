#include "TileManager.h"
#include"MapConst.h"
#include"MapCreate.h"
#include"MapManager.h"
#include"TileObject.h"
#include"../../Utility/Game.h"
#include"../../Utility/Color.h"
#include"../../Utility/MyRandom.h"
#include"../../Utility/Game.h"
#include"../Character/Player/Player.h"
#include"../Object/Stair.h"
#include<DxLib.h>
#include<vector>

namespace {
	constexpr Vector3 blockSize = { 5.0f,5.0f ,0.0f };
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
	constexpr Vector3 kMapSize = { MapConst::kTileUnscaledSize * MapConst::MAP_SQUARE_WIDTH_COUNT,MapConst::kTileUnscaledSize  * MapConst::MAP_SQUARE_HEIGHT_COUNT,0.0f };
	constexpr float kCursorScale = 0.20f;
	const char* const kCursorPath = "Resource\\UI\\MapPlayerCursor.png";
	const char* const kWallPath = "Resource\\Map\\wall.mv1";
	const char* const kFloorPath = "Resource\\Map\\floor.mv1";
}

TileManager::TileManager() :
	m_markPos(),
	m_cursorHandle(-1),
	m_pTiles(),
	stair(nullptr),
	m_upStair(false),
	m_pPlayer(nullptr),
	m_pad(Input::Pad::Invalid)
{
	m_cursorHandle = LoadGraph(kCursorPath);

	m_wallHandle = MV1LoadModel(kWallPath);
	m_floorHandle = MV1LoadModel(kFloorPath);
	stair = std::make_unique<Stair>();
	// フロア生成
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
	// 階段に登れるかどうかを初期化
	m_upStair = false;
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
	m_stairID = RandomRoomID();
	stair->SetTile(m_stairID);
}

void TileManager::Update(float deltaTime)
{
	// マップの描画処理
	for (auto& tile : m_pTiles) {
		tile->Update(deltaTime);
	}
	if (stair) {
		stair->Update(deltaTime);
	}

	if (Input::IsPressed(Input::Button::B, m_pad)) {
		if (IsUpStair()) {
			// フロア生成
			SetUpFloor();
			// 部屋マスの中でランダムなIDを取得
			int randomID = MyRandom::ArrayRandom(MapCreate::GetInstance().GetRooms());
			//取得したマスのIDからマスの座標を計算
			Vector3 initPos = MapManager::GetInstance().GetWorldPosFromID(randomID);
			// ランダムな部屋マスにプレイヤーを生成
			m_pPlayer->SetFirstPos(initPos);
		}
	}
}

void TileManager::Draw()
{
	// マップの描画処理
	for (int i = 0; i < m_pTiles.size();i++) {
		if (i == m_stairID) {
			continue;
		}
		m_pTiles[i]->Draw();
	}
	if (stair) {
		stair->Draw();
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
	DrawRotaGraph(toMapPos.x, toMapPos.y, kCursorScale, m_markPos.rotation.y, m_cursorHandle, TRUE);
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

Collision::Result TileManager::CheckCollision(GameObject* object)
{
	Collision::Result result;
	// 引数オブジェクトの座標から現在いるマスを取得
	int targetTileID = MapManager::GetInstance().GetIDFromWorldPos(object->GetTransform().position);
	if (targetTileID == -1)return result;
	// 現在いるマスの周囲マスを取得
	std::vector<int>chebyshevID = MapManager::GetInstance().CheckChebyshevID(targetTileID);
	// 現在のマスを追加
	chebyshevID.push_back(targetTileID);
	// 引数オブジェクトの周囲8マスだけ当たり判定をチェック
	for (int& tileID:chebyshevID) {
		result = m_pTiles[tileID]->CheckCollision(object);
	}


	if (object->GetCollisionTag() == GameObject::CollisionTag::Player) {
		Collision::Result stairResult= stair->GetCollision().CheckCollision(object->GetCollision());
		m_upStair = stairResult.isHit;
		stair->SetIsHit(m_upStair);
		stair->SetBillboardPos(object->GetTransform().position);
	}
	return result;
}