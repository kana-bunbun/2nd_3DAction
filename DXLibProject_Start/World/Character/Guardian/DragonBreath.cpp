#include "DragonBreath.h"
#include "../../../Utility/Color.h"
#include"../../../System/TimeManager.h"
namespace {
	constexpr float kMoveSpeed = 500.0f;
	constexpr float kDeleteCount = 3.0f;
}
DragonBreath::DragonBreath()
{
	m_transform.Reset();
}

DragonBreath::~DragonBreath()
{

}

void DragonBreath::Init()
{

}

void DragonBreath::Setup(const Vector3& RegistPos, const Vector3& moveVec)
{
	m_transform.position = RegistPos;
	m_moveVec = moveVec.Normalize();
	m_isActive = true;

	m_lifeCount = 0.0f;
}


void DragonBreath::Update(float deltaTime)
{
	m_transform.position += m_moveVec * kMoveSpeed * deltaTime;
	m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
	m_lifeCount += deltaTime;

	// 生成されてから一定時間たつと削除
	if (m_lifeCount < kDeleteCount)return;
	m_isActive = false;

}

void DragonBreath::Draw()
{
	DrawSphere3D(m_transform.position.ToVECTOR(), 30, 10, Color::kMagenta, Color::kMagenta, TRUE);
}

void DragonBreath::ResolveCollision(GameObject& other, const CollisionData& myData, const CollisionData& otherData, const Collision::Result& result)
{}
