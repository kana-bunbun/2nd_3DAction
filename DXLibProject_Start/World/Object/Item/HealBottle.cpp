#include "HealBottle.h"
#include "../../../System/ResourceManager.h"

namespace {
	const char* const kModelPath = "bottlePotionHealth";
}

HealBottle::HealBottle()
{
	m_modelHandle = ResourceManager::GetInstance().GetModel(kModelPath, ResourceManager::FileName::Item);
}

HealBottle::~HealBottle()
{
	MV1DeleteModel(m_modelHandle);
}

void HealBottle::Init()
{

}

void HealBottle::End()
{

}

void HealBottle::Setup(const Transform& transform)
{
	m_transform.position = transform.position;
}

void HealBottle::Update(float deltaTime)
{

}

void HealBottle::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{

}
