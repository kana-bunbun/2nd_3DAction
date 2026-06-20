#include "Stair.h"
#include"../Map/MapManager.h"
#include"../UI/BillboardManager.h"
namespace {
	constexpr Vector3 kBillboardOffset = { 0.0f,100.0f,0.0f };
}
Stair::Stair()
{
	m_transform.Reset();
}

Stair::~Stair()
{

}

void Stair::Init()
{

}

void Stair::Update(float deltaTime)
{
	DrawSphere3D(m_transform.position.ToVECTOR(), 50, 10, 0xffff00, 0xffff00, TRUE);

	Vector3 billboardPos = m_transform.position + kBillboardOffset;
	BillboardManager::GetInstance().DrawBillboard(billboardPos, 0, 0, 500, 0, BillboardManager::eBillboard::Stair);
}

void Stair::ResolveCollision(GameObject & other, const Collision::Result & result)
{

}

void Stair::SetTile(int tileID)
{
	m_transform.position = MapManager::GetInstance().GetWorldPosFromID(tileID);
}
