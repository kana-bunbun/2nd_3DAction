#include "UIManager.h"
#include"GaugeShow.h"
#include"GaugePlayer.h"
#include"GaugeDragon.h"
#include<memory>
UIManager::UIManager():
	m_pPlayer(nullptr),
	m_pDragon(nullptr),
	m_gaugePlayer(nullptr),
	m_gaugeDragon(nullptr)
{
	m_gaugePlayer = std::make_unique<GaugePlayer>();
	m_gaugeDragon = std::make_unique<GaugeDragon>();
}

UIManager::~UIManager()
{
	if (m_pPlayer) {
		m_pPlayer = nullptr;
		delete m_pPlayer;
	}
	if (m_pDragon) {
		m_pDragon = nullptr;
		delete m_pDragon;
	}
}

void UIManager::Init()
{
	m_gaugePlayer->Init();
	m_gaugeDragon->Init();
}

void UIManager::End()
{
	m_gaugePlayer->End();
	m_gaugeDragon->End();
}

void UIManager::Update()
{
	m_gaugePlayer->Update();
	m_gaugeDragon->Update();
}

void UIManager::Draw()
{
	m_gaugePlayer->Draw();
	m_gaugeDragon->Draw();

}

void UIManager::SetPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
	if(m_gaugePlayer)
	m_gaugePlayer->SetPlayer(pPlayer);
}

void UIManager::SetDragon(Dragon* pDragon)
{
	m_pDragon = pDragon;
	if (m_gaugeDragon)
		m_gaugeDragon->SetDragon(pDragon);

}
