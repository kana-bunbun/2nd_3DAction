#include "TileObject.h"
#include "../../Utility/Color.h"
#include"MapTile.h"
#include"MapManager.h"
namespace {
	constexpr Vector3 kFloorSize = { MapConst::kFloorScale,MapConst::kFloorScale*25 ,MapConst::kFloorScale };
	constexpr float kWallDistance = MapConst::kTileUnscaledSize * (0.5f);
	constexpr Vector3 kWallSize = { MapConst::kWallScale ,MapConst::kWallScale ,MapConst::kWallScale };
	constexpr Vector3 kModelOffset = { 0,-kFloorSize.y*5 ,0};
	constexpr Vector3 kCollisionOffset = { 0,200*MapConst::kWallScale ,0};

	constexpr float kCollisionSIzeX = 396 * MapConst::kWallScale;
	constexpr float kCollisionSIzeZ = 180 * MapConst::kWallScale;
	constexpr Vector3 kWallCollisionX = { kCollisionSIzeX,kCollisionSIzeX,kCollisionSIzeZ };
	constexpr Vector3 kWallCollisionZ = { kCollisionSIzeZ ,kCollisionSIzeX ,kCollisionSIzeX };
}

TileObject::TileObject(int ID, const Vector3& position, const MapConst::eTerrain& terrain) :
	m_ID(ID),
	m_wallDirection(),
	m_wallPos(),
	m_wallHandle(-1),
	m_terrain(terrain)
{
	m_transform.position = position;
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionFour::Max); i++) {
		// 方向を調べる
		MapConst::eDirectionFour direction = static_cast<MapConst::eDirectionFour>(i);
		AddCollision(std::make_unique<Collision::AABB>(), CollisionType::Invalid);
		RegistWall(direction);
	}
	ChangeTile(ID, position, terrain);

	m_isStair = false;
}

TileObject::~TileObject()
{

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

void TileObject::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{}

void TileObject::Draw()
{
	if (m_terrain == MapConst::eTerrain::Invalid)return;

	// 階段マスなら描画しない
	if (m_isStair)return;
	// モデルが読み込まれているかどうかチェック
	if (m_modelData->GetHandle() != -1) {
		Vector3 pos = m_transform.position + kModelOffset;
	MV1SetRotationXYZ(m_modelData->GetHandle(), m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelData->GetHandle(), pos.ToVECTOR());
	MV1DrawModel(m_modelData->GetHandle());
	}

	// 壁マスでなければ処理しない
	//if (m_terrain != MapConst::eTerrain::Wall)return;
	// 隣接する壁の方向だけ描画
	for (int i = 0; i < m_wallPos.size();i++) {
		if (m_wallHandle == -1||
			!m_wallDirection[i])continue;
		MV1SetRotationXYZ(m_wallHandle, m_wallPos[i].rotation.ToVECTOR());
		MV1SetPosition(m_wallHandle, m_wallPos[i].position.ToVECTOR());
		MV1DrawModel(m_wallHandle);
	}
}

void TileObject::SetFloorModel(ModelData* modelData)
{
	m_modelData = modelData;
	MV1SetScale(m_modelData->GetHandle(), kFloorSize.ToVECTOR());
	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { 0.1f,0.1f,0.1f,1.0f };
	MV1SetMaterialEmiColor(m_modelData->GetHandle(), 0, color);
}


void TileObject::SetWallHandle(ModelData* wallData)
{
	m_wallModelData = wallData;
	MV1SetScale(m_wallModelData->GetHandle(), kWallSize.ToVECTOR());

	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { 0.3f,0.3f,0.3f,1.0f };
	MV1SetMaterialEmiColor(m_wallHandle, 0, color);

}

void TileObject::RegistWall(const MapConst::eDirectionFour& direction)
{
	Transform regist;
	regist.Reset();
	regist.position.y -= 100;
	int wallNum = static_cast<int>(direction);
	Vector3 collisionSize = Vector3::zero;
	switch (direction)
	{
	case MapConst::eDirectionFour::Up:
	{
		regist.position = Vector3::ZAxis * kWallDistance;
		regist.rotation.y = DX_PI_F * 0.5f;
		collisionSize = kWallCollisionZ;
		break;
	}
	case MapConst::eDirectionFour::Right:
		regist.position = Vector3::XAxis * kWallDistance;
		collisionSize = kWallCollisionX;
		break;
	case MapConst::eDirectionFour::Down:
		regist.position = -Vector3::ZAxis * kWallDistance;
		regist.rotation.y = DX_PI_F * 0.5f;
		collisionSize = kWallCollisionZ;
		break;
	case MapConst::eDirectionFour::Left:
		regist.position = -Vector3::XAxis * kWallDistance;
		collisionSize = kWallCollisionX;
		break;

	case MapConst::eDirectionFour::Invalid:
	case MapConst::eDirectionFour::Max:
	default:
		return;
	}
	std::unique_ptr<Collision::Shape> shape = std::make_unique<Collision::AABB>(kCollisionOffset+regist.position, collisionSize);
	regist.position += m_transform.position;
	m_collisions[wallNum].shape = std::move(shape);
	m_collisions[wallNum].shape ->SetPosition(regist.position);
	m_collisionTag = CollisionTag::Wall;
	// 自身の座標から見た壁の座標を追加
	m_wallPos.push_back(regist);
}

void TileObject::ChangeTile(int ID, const Vector3& position, const MapConst::eTerrain& terrain)
{
	m_ID = ID;
	m_transform.position = position;
	m_terrain = terrain;
	CheckWall();
}


void TileObject::CheckWall()
{
	// 壁方向を初期化
	m_wallDirection.fill(false); 

	// 4方向を調べ隣接している壁の方向を取得
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionFour::Max); i++) {
		m_collisions[i].type = CollisionType::Null;
		if (m_terrain != MapConst::eTerrain::Wall)continue;
		// 方向を調べる
		MapConst::eDirectionFour direction = static_cast<MapConst::eDirectionFour>(i);
		MapTile* tile = MapManager::GetInstance().GetToDirSquare(m_ID, direction);
		if (!tile || tile->GetSquareData()->GetTerrain() != MapConst::eTerrain::Wall)
		{
			continue;
		}
		m_wallDirection[i] = true;
		m_collisions[i].type = CollisionType::Normal;

	}

}

