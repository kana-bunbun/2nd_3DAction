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

	constexpr float kCollisionSIzeX = 400 * MapConst::kWallScale;
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
		m_collisions[i] = std::make_unique<Collision::AABB>();
		RegistWall(direction);
	}
	ChangeTile(ID, position, terrain);
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

void TileObject::ResolveCollision(GameObject::CollisionTag tag, const Collision::Result & result)
{}

void TileObject::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{}

void TileObject::Draw()
{
	if (m_terrain == MapConst::eTerrain::Invalid)return;
	// モデルが読み込まれているかどうかチェック
	if (m_modelHandle != -1) {
		Vector3 pos = m_transform.position + kModelOffset;
	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, pos.ToVECTOR());
	MV1DrawModel(m_modelHandle);
	}

	// 壁マスでなければ処理しない
	if (m_terrain != MapConst::eTerrain::Wall)return;
	// 隣接する壁の方向だけ描画
	for (int i = 0; i < m_wallPos.size();i++) {
		if (m_wallHandle == -1||
			!m_wallDirection[i])continue;
		MV1SetRotationXYZ(m_wallHandle, m_wallPos[i].rotation.ToVECTOR());
		MV1SetPosition(m_wallHandle, m_wallPos[i].position.ToVECTOR());
		MV1DrawModel(m_wallHandle);
		if (m_collisions[i]) {
			m_collisions[i]->DebugDraw();
		}
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

void TileObject::RegistWall(const MapConst::eDirectionFour& direction)
{
	Transform regist;
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
	regist.position += m_transform.position;
	std::unique_ptr <Collision::AABB> collision = std::make_unique<Collision::AABB>(kCollisionOffset, collisionSize);
	m_collisions[wallNum] = std::move(collision);
	m_collisions[wallNum] ->SetPosition(regist.position);
	m_collisionTag = GameObject::CollisionTag::Wall;
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

	if (m_terrain != MapConst::eTerrain::Wall)return;
	// 4方向を調べ隣接している壁の方向を取得
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionFour::Max); i++) {
		// 方向を調べる
		MapConst::eDirectionFour direction = static_cast<MapConst::eDirectionFour>(i);
		MapTile* tile = MapManager::GetInstance().GetToDirSquare(m_ID, direction);
		if (!tile || tile->GetSquareData()->GetTerrain() != MapConst::eTerrain::Wall)continue;
		m_wallDirection[i] = true;
	}

}

Collision::Result TileObject::CheckCollision(GameObject* object)
{
	Collision::Result result;
	Vector3 resolve = Vector3::zero;
	for (int i = 0; i < m_collisions.size();i++) {
		if (!m_wallDirection[i])continue;
		result=m_collisions[i]->CheckCollision(object->GetCollision());
		object->ResolveCollision(GameObject::CollisionTag::Wall, result);
		if (!result.isHit)continue;
	}
	return result;
}
