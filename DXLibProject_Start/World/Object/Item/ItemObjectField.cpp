#include"pch.h"
#include "ItemObjectField.h"
#include "../../UI/ItemCursor.h"
#include"World/Component/Collision/Collision.h"
#include"World/Component/Collision/CollisionShape.h"
namespace {
	constexpr float kSphereRadius = 50.0f;
	constexpr Vector3 kCollisionSize = { 100,300,100 };
}
ItemObjectField::ItemObjectField()
{
	AddCollision(std::make_unique<Collision::AABB>(m_transform.position, kCollisionSize), CollisionType::Body);
}

ItemObjectField::~ItemObjectField()
{

}

void ItemObjectField::Init()
{
	m_hitLog.fill(false);
}

void ItemObjectField::End()
{

}

void ItemObjectField::Update(float deltaTime, const InputData& _inputData)
{
	m_hitLog[0] = m_hitLog[1];
	m_hitLog[1] = false;
	PickUpItem(_inputData);
}

void ItemObjectField::Draw()
{
	Vector3 drawPos = m_transform.position;
	drawPos.y += kCollisionSize.y*0.5f;
	DrawSphere3D(drawPos.ToVECTOR(), kSphereRadius, 10, Color::kYellow, Color::kYellow, TRUE);
}

void ItemObjectField::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{
	switch (other.GetCollisionTag())
	{
	case CollisionTag::Player:
		m_hitLog[1] = true;
		break;
	default:
		break;
	}
}

void ItemObjectField::PickUpItem(const InputData& _inputData)
{
	InputData input = _inputData;
	if (!m_hitLog[0])return;
	if (!input.IsPressed(Input::Action::PickUpItem))return;

	if (!m_pItemCursor || !m_pItemCursor->AddItem(m_type))return;
	m_isActive = false;
}

void ItemObjectField::Setup(const ItemData::Type& type, const Vector3& position)
{
	m_isActive = true;
	m_hitLog.fill(false);
	m_type = type;
	m_transform.position = position;
}
