#include "pch.h"
#include "DragonAttack.h"
namespace {
	constexpr int kAttackInterval = 1;
}
DragonAttack::DragonAttack():
	m_attackCount(0.0f),
	m_active(false),
	m_attackFlag(false)
{

}

DragonAttack::~DragonAttack()
{

}

void DragonAttack::Init()
{

}

void DragonAttack::Update(float deltaTime)
{
	m_attackCount+=deltaTime;
	m_attackFlag = false;
	if (m_attackCount < kAttackInterval)return;
	m_attackFlag = true;
}

void DragonAttack::End()
{

}



