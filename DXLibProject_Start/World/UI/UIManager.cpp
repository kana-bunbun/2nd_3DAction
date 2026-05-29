#include "UIManager.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

void UIManager::Init()
{

}

void UIManager::End()
{
	for (auto& gaugeShow : m_gaugeShow)
		gaugeShow->End();
}

void UIManager::Update()
{
	for (auto& gaugeShow : m_gaugeShow)
		gaugeShow->Update();
}

void UIManager::Draw()
{
	for (auto& gaugeShow : m_gaugeShow)
		gaugeShow->Draw();
}

void UIManager::AddGauge(const Vector3& position, int type, Gauge* gauge)
{
	std::unique_ptr<GaugeShow>gaugeShow = std::make_unique<GaugeShow>(position, type);
	gaugeShow->SetGauge(gauge);
	m_gaugeShow.push_back(std::move(gaugeShow));
}

