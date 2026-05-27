#include "CharacterMove.h"

CharacterMove::CharacterMove():
	m_transform(),
	m_desireRad(0),
	m_speed(0)
{

}

CharacterMove::~CharacterMove()
{

}

void CharacterMove::Init()
{

}

void CharacterMove::End()
{

}

void CharacterMove::Update()
{

	// プレイヤーの角度の補間量
	float lerpRad = (m_desireRad - m_transform.rotation.y);
	// 角度を180～-180の間に収める
	lerpRad = MyMath::NormalizeRadian(lerpRad);
	// 補間割合をかける
	lerpRad *= m_lerpSpeed;
	// 
	m_transform.rotation.y += lerpRad;
	m_transform.rotation.y = MyMath::NormalizeRadian(m_transform.rotation.y);


	Vector3 moveVec = Vector3::zero;
	moveVec.x = -sinf(m_transform.rotation.y);
	moveVec.z = -cosf(m_transform.rotation.y);
	moveVec *= m_speed;
	m_transform.position += moveVec;
}
