#include "UIManager.h"
#include"GaugeShow.h"
#include"GaugePlayer.h"
#include<memory>
UIManager::UIManager():
	m_pPlayer(nullptr),
	m_gaugePlayer(nullptr)
{
	m_gaugePlayer = std::make_unique<GaugePlayer>();
}

UIManager::~UIManager()
{
	if (m_pPlayer) {
		m_pPlayer = nullptr;
		delete m_pPlayer;
	}
}

void UIManager::Init()
{
	m_gaugePlayer->Init();
}

void UIManager::End()
{
	m_gaugePlayer->End();
}

void UIManager::Update()
{
	m_gaugePlayer->Update();
}

void UIManager::Draw()
{
	m_gaugePlayer->Draw();

}

void UIManager::SetPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
	if(m_gaugePlayer)
	m_gaugePlayer->SetPlayer(pPlayer);
}
