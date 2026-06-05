#include "CharaGaugeManager.h"
#include "../UI/GaugeShow.h"
#include "../UI/Gauge.h"
#include"../Character/Player/Player.h"
#include"../Character/Guardian/Dragon.h"

#include"../../Utility/Input.h"

CharaGaugeManager::CharaGaugeManager():
	m_pPlayer(nullptr),
	m_PlayerGauges(),
	m_DragonGauges()
{

}

CharaGaugeManager::~CharaGaugeManager()
{

}

void CharaGaugeManager::Init()
{

}

void CharaGaugeManager::Update()
{
	if (Input::IsDown(Input::Button::LB, Pad::Player::P1)) {
		for (std::shared_ptr<Gauge>& gauge : m_PlayerGauges) {
			gauge->Increase(1);
			gauge->Clamp();
		}
		for (std::shared_ptr<Gauge>& gauge : m_DragonGauges) {
			gauge->Increase(1);
			gauge->Clamp();
		}

	}
	if (Input::IsDown(Input::Button::RB, Pad::Player::P1)) {
		for (std::shared_ptr<Gauge>& gauge : m_PlayerGauges) {
			gauge->Decrease(1);
			gauge->Clamp();
		}
		for (std::shared_ptr<Gauge>& gauge : m_DragonGauges) {
			gauge->Decrease(1);
			gauge->Clamp();
		}
	}
}

void CharaGaugeManager::End()
{

}

void CharaGaugeManager::SetPlayer(std::shared_ptr<Player> pPlayer)
{
	m_pPlayer = pPlayer;
	m_PlayerGauges = m_pPlayer->GetGauge();
}

void CharaGaugeManager::SetDragon(std::shared_ptr<Dragon> pDragon)
{
	m_pDragon = pDragon;
	m_DragonGauges.push_back(m_pDragon->GetGauge());
}
