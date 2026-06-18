#include "FloorTile.h"

FloorTile::FloorTile(int ID, Vector3 position)
{
	m_ID = ID;
	m_transform.position = position;
}

FloorTile::~FloorTile()
{
	MV1DeleteModel(m_modelHandle);

}

void FloorTile::ResolveCollision(GameObject & other, const Collision::Result & result)
{}

void FloorTile::Draw()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelHandle == -1)return;
	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelHandle);
}
