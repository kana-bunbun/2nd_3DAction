#include "TileObject.h"
#include "../../Utility/Color.h"
#include"MapTile.h"
#include"MapManager.h"
namespace {
	constexpr Vector3 kFloorSize = { MapConst::kFloorScale,MapConst::kFloorScale ,MapConst::kFloorScale };
	constexpr float kWallDistance = MapConst::kTileSize * (0.5f);
	constexpr Vector3 kWallSize = { MapConst::kWallScale ,MapConst::kWallScale ,MapConst::kWallScale };
}
TileObject::TileObject(int ID, Vector3 position,MapConst::eTerrain terrain):
	m_ID(ID),
	m_wallDirection(),
	m_wallPos(),
	m_wallHandle(-1),
	m_terrain(terrain)
{
	ChangeTile(ID, position, terrain);

	/*Vector3 size = { MapConst::kTileSize,MapConst::kTileSize,MapConst::kTileSize };
	size *= 0.5f;
	m_collision = std::make_unique<Collision::AABB>(Vector3::zero, size);
	m_collision->SetPosition(m_transform.position);*/

}

TileObject::~TileObject()
{
	MV1DeleteModel(m_modelHandle);
	MV1DeleteModel(m_wallHandle);
}

void TileObject::Init()
{

}

void TileObject::End()
{

}

void TileObject::Update(float deltaTime)
{
}

void TileObject::ResolveCollision(GameObject& other, const Collision::Result& result)
{}

void TileObject::Draw()
{
	if (m_terrain == MapConst::eTerrain::Invalid)return;
	// モデルが読み込まれているかどうかチェック
	if (m_modelHandle == -1)return;
	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelHandle);

	// 壁マスで鳴けば処理しない
	if (m_terrain != MapConst::eTerrain::Wall)return;
	// 隣接する壁の方向だけ描画
	for (Transform& wallPos : m_wallPos) {
		if (m_wallHandle == -1)continue;
		MV1SetRotationXYZ(m_wallHandle, wallPos.rotation.ToVECTOR());
		MV1SetPosition(m_wallHandle, wallPos.position.ToVECTOR());
		MV1DrawModel(m_wallHandle);
	}


}

void TileObject::SetFloorModel(int modelHandle)
{
	m_modelHandle = modelHandle;
	MV1SetScale(m_modelHandle, kFloorSize.ToVECTOR());
	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { 0.1f,0.1f,0.1f,1.0f };
	MV1SetMaterialEmiColor(m_modelHandle, 0, color);
}


void TileObject::SetWallHandle(int wallHandle)
{
	m_wallHandle = wallHandle;
	MV1SetScale(m_wallHandle, kWallSize.ToVECTOR());

	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { 0.3f,0.3f,0.3f,1.0f };
	MV1SetMaterialEmiColor(m_wallHandle, 0, color);

}

void TileObject::RegistWallPos(MapConst::eDirectionFour direction)
{
	Transform regist;
	switch (direction)
	{
	case MapConst::eDirectionFour::Up:
		regist.position = Vector3::ZAxis * kWallDistance;
		regist.rotation.y = DX_PI_F * 0.5f;
		break;
	case MapConst::eDirectionFour::Right:
		regist.position = Vector3::XAxis * kWallDistance;
		break;
	case MapConst::eDirectionFour::Down:
		regist.position = -Vector3::ZAxis * kWallDistance;
		regist.rotation.y = DX_PI_F * 0.5f;
		break;
	case MapConst::eDirectionFour::Left:
		regist.position = -Vector3::XAxis * kWallDistance;
		break;

	case MapConst::eDirectionFour::Invalid:
	case MapConst::eDirectionFour::Max:
	default:
		return;
	}
	regist.position += m_transform.position;
	// 自身の座標から見た壁の座標を追加
	m_wallPos.push_back(regist);
}

void TileObject::ChangeTile(int ID,Vector3 position,MapConst::eTerrain terrain)
{
	m_ID = ID;
	m_transform.position = position;
	m_terrain = terrain;
	CheckWall();
}

void TileObject::CheckWall()
{
	// 壁方向を初期化
	m_wallDirection.clear(); 
	// 壁座標を初期化
	m_wallPos.clear();
	// 4方向を調べ隣接している壁の方向を取得
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionFour::Max); i++) {
		// 方向を調べる
		MapConst::eDirectionFour direction = static_cast<MapConst::eDirectionFour>(i);
		MapTile* tile = MapManager::GetInstance().GetToDirSquare(m_ID, direction);
		if (!tile || tile->GetSquareData()->GetTerrain() != MapConst::eTerrain::Wall)continue;
		RegistWallPos(direction);
	}

}
