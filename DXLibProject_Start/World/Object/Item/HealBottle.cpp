#include "HealBottle.h"
#include "../../../System/ResourceManager.h"
#include"../../../Utility/MyRandom.h"
namespace {
	const char* const kModelPath = "bottlePotionHealth";

	// 投げる力の強さ
	constexpr float kThrowPower=1200.0f;
	// 落下速度
	constexpr float kFallSpeed = kThrowPower *2.5f;
	// 回転速度の最大値
	constexpr float kRotateSpeedMax = DX_PI_F * 1.3f;
	// 描画の中心となるフレームの位置
	constexpr int kDrawCenterFrameNum = 1;
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
	m_isActive = true;
	m_transform.position = transform.position;
	
	m_rotateSpeed.x= MyRandom::Float(0, kRotateSpeedMax);
	m_rotateSpeed.y= MyRandom::Float(0, kRotateSpeedMax);
	m_rotateSpeed.z= MyRandom::Float(0, kRotateSpeedMax);
	m_transform.rotation = m_rotateSpeed;
	m_fallSpeed = kThrowPower;
}

void HealBottle::Update(float deltaTime)
{
	m_transform.rotation += m_rotateSpeed * deltaTime;
	m_fallSpeed -= kFallSpeed * deltaTime;
	m_transform.position.y += m_fallSpeed * deltaTime;
	if (m_transform.position.y < 0) {
		m_fallSpeed = 0;
		m_transform.position.y = 0;
		m_isActive = false;
	}
}

void HealBottle::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{

}
