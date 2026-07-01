#include "FloorBlock.h"

namespace {
	const char* const kModelPath = "Resource\\Cube_Grass_Single.mv1";
	constexpr Vector3 kInitPos = { 0.0f,-100.0f,0.0f };
	constexpr Vector3 kOffsetPos = { 0.0f,0.0f,0.0f };
	constexpr Vector3 kInitSize = { 1.0f,1.0f,1.0f };
	constexpr Vector3 kCollisionSize = { 200.0f,200.0f,200.0f };
}

FloorBlock::FloorBlock()
{
	m_modelHandle = MV1LoadModel(kModelPath);
	MV1SetScale(m_modelHandle, kInitSize.ToVECTOR());
	m_collisionTag = GameObject::CollisionTag::Stage;
	AddCollision(std::make_unique<Collision::AABB>(kOffsetPos, kCollisionSize), GameObject::CollisionType::Body);
}

void FloorBlock::Init()
{

}

void FloorBlock::Update(float deltaTime)
{
}

void FloorBlock::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{}
