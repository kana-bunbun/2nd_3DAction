#include "Enemy.h"
namespace {

}

Enemy::Enemy():
	m_animation(),
	m_animData(),
	m_status(),
	m_animHandle(),
	m_desireRad()
{
}

Enemy::~Enemy()
{}

void Enemy::Init()
{}

void Enemy::Update()
{}

void Enemy::ResolveCollision(const Collision::Result & result)
{}
