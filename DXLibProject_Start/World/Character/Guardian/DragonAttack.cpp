#include "DragonAttack.h"
namespace {
	constexpr int kAttackCount = 60;
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

void DragonAttack::Update()
{
	m_attackCount++;
	m_attackFlag = false;
	if (m_attackCount < 60)return;
	m_attackFlag = true;
}

void DragonAttack::End()
{

}



