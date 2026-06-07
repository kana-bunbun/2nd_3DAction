#include "Enemy.h"
namespace {
	const char* const kModelPath = "Resource\\Enemy\\Queen\\Model.mv1";
}

Enemy::Enemy():
	m_animation(),
	m_animData(),
	m_status(),
	m_animHandle(),
	m_desireRad()
{
	//m_modelHandle=MV1Loadmm
}

Enemy::~Enemy()
{}

void Enemy::Init()
{}

void Enemy::Update()
{}

void Enemy::ResolveCollision(GameObject& other, const Collision::Result & result)
{}
