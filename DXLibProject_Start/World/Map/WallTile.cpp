#include "WallTile.h"
#include "MapConst.h"
#include "MapManager.h"
#include "MapTile.h"
#include "../Component/Collision.h"

namespace {
	constexpr float kWallDistance = MapConst::kTileSize * (0.5f);
	constexpr Vector3 kWallSize = { MapConst::kWallScale ,MapConst::kWallScale ,MapConst::kWallScale };
}

WallTile::WallTile(int ID, Vector3 position) :
	m_wallDirection(),
	m_wallPos(),
	m_wallHandle()
{
	m_ID = ID;
	m_transform.position = position;

	// 4方向を調べ隣接している壁の方向を取得
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionFour::Max); i++) {
		// 方向を調べる
		MapConst::eDirectionFour direction = static_cast<MapConst::eDirectionFour>(i);
		MapTile* tile = MapManager::GetInstance().GetToDirSquare(m_ID, direction);
		if(!tile||tile->GetSquareData()->GetTerrain() != MapConst::eTerrain::Wall)continue;
		RegistWallPos(direction);
	}
	Vector3 size = { MapConst::kTileSize,MapConst::kTileSize,MapConst::kTileSize };
	size *= 0.5f;
	m_collision = std::make_unique<Collision::AABB>(Vector3::zero, size);
	m_collision->SetPosition(m_transform.position);
}

WallTile::~WallTile()
{
	MV1DeleteModel(m_modelHandle);
	MV1DeleteModel(m_wallHandle);
}

void WallTile::ResolveCollision(GameObject& other, const Collision::Result& result)
{}

void WallTile::Draw()
{
	for (Transform& wallPos : m_wallPos) {
		if (m_wallHandle == -1)continue;
		MV1SetRotationXYZ(m_wallHandle, wallPos.rotation.ToVECTOR());
		MV1SetPosition(m_wallHandle, wallPos.position.ToVECTOR());
		MV1DrawModel(m_wallHandle);
	}
	Vector3 ps = m_transform.position*0.5f;
	m_collision->SetPosition(m_transform.position);
	DrawSphere3D(m_transform.position.ToVECTOR(), 20, 10, 0xffff00, 0xffff00, TRUE);
	m_collision->DebugDraw();
	Vector3 colpos=m_collision->GetPos();
	printfDx("      colPos X : %f | Y : %f | Z : %f\n", colpos.x, colpos.y, colpos.z);
	printfDx("transformPos X : %f | Y : %f | Z : %f\n", m_transform.position.x, m_transform.position.y, m_transform.position.z);
	// モデルが読み込まれているかどうかチェック
	if (m_modelHandle == -1)return;
	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelHandle);
}

void WallTile::SetWallHandle(int wallHandle)
{
	m_wallHandle = wallHandle;
	MV1SetScale(m_wallHandle,kWallSize.ToVECTOR());

	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { 0.3f,0.3f,0.3f,1.0f };
	MV1SetMaterialEmiColor(m_wallHandle, 0, color);

}

void WallTile::RegistWallPos(MapConst::eDirectionFour direction)
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

