#include "DragonBreath.h"
#include "../../../Utility/Color.h"

DragonBreath::DragonBreath() :
	m_transform(),
	m_isActive(false)
{
	m_transform.Reset();
}

DragonBreath::~DragonBreath()
{

}

void DragonBreath::Init(const Transform& transform)
{
	m_transform = transform;
	m_isActive = true;
}

void DragonBreath::End()
{

}

void DragonBreath::Update(float deltaTime)
{
	if (!m_isActive)return;
	Vector3 moveVector = Vector3::zero;
	moveVector.x = sinf(m_transform.rotation.y);
	moveVector.y = sinf(m_transform.rotation.x);
	moveVector.z = cosf(m_transform.rotation.y);
	moveVector = moveVector.Normalize();
	m_transform.position += moveVector;
}

void DragonBreath::Draw()
{
	if (!m_isActive)return;
	DrawSphere3D(m_transform.position.ToVECTOR(), 30, 10, Color::kMagenta, Color::kMagenta, TRUE);
}
