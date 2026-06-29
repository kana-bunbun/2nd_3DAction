#include "EnemyManager.h"
#include "Enemy.h"
#include "../../Map/MapCreate.h"
#include "../../Map/MapManager.h"
#include "../../../Utility/MyRandom.h"
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

void EnemyManager::Update(float deltaTime)
{
	for (auto& enemy : m_enemys)
		enemy->Update(deltaTime);
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

void EnemyManager::RegistRandomPos()
{
	std::vector<int>rooms = MapCreate::GetInstance().GetRooms();
	int roomNum = MyRandom::Int(0, rooms.size() - 1);

	Vector3 randomPos = MapManager::GetInstance().GetWorldPosFromID(rooms[roomNum]);
	for (auto& enemy : m_enemys) {
		enemy->SetPosition(randomPos);
	}
}

