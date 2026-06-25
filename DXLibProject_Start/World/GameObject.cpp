#include "GameObject.h"

#include<DxLib.h>
#include<cassert>

#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"
#include"../World/Component/Collision.h"


GameObject::GameObject():
m_transform(),
m_modelHandle(-1),
m_collision(),
m_isActive(true)
{
}

void GameObject::End()
{
	// モデルを読み込んでいたら破棄
	if (m_modelHandle != -1){
		MV1DeleteModel(m_modelHandle);
		m_modelHandle = -1;
	}
}


void GameObject::Draw()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelHandle == -1)return;
	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelHandle);

	if (m_collision)m_collision->DebugDraw();
	for (const auto& collision : m_collisions) {
		if (collision.shape)collision.shape->DebugDraw(Color::kGreen);
	}
}

const Collision::Shape& GameObject::GetCollision() const
{
	for (const auto& collision : m_collisions) {
		if (collision.type == CollisionType::Body) {
			return *collision.shape;
		}
	}
	return *m_collision;
	return *m_collisions.front().shape;
}

void GameObject::AddCollision(std::unique_ptr<Collision::Shape> shape, CollisionType type)
{
	assert(shape && "GameCbject::AddCOllision : shape null");

	m_collisions.push_back({ std::move(shape),type });
}
