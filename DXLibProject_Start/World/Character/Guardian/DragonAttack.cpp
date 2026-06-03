#include "DragonAttack.h"
#include"../../../Utility/Time.h"
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

void DragonAttack::Update()
{
	m_attackCount+=Time::GetInstance().GetDeltaTime();
	m_attackFlag = false;
	if (m_attackCount < kAttackInterval)return;
	m_attackFlag = true;
}

void DragonAttack::End()
{

}



