#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager():
	m_enemys()
{
	m_enemys.emplace_back(std::make_unique<Enemy>());
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Init()
{
	for (auto& enemy : m_enemys)
		enemy->Init();
}

void EnemyManager::End()
{
	for (auto& enemy : m_enemys)
		enemy->End();
}

void EnemyManager::Update()
{
	for (auto& enemy : m_enemys)
		enemy->Update();
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_enemys)
		enemy->Draw();
}

void EnemyManager::CreateEnemy(const Transform& createTransform)
{
	m_enemys.emplace_back(std::make_unique<Enemy>());

}

void EnemyManager::SetTarget(GameObject* target)
{
	for (auto& enemy : m_enemys)
		enemy->SetTarget(target);
}

