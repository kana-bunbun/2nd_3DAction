#include "CollisionDataManager.h"
#include"../World/GameObjectParam.h"
#include"../Utility/Data.h"
#include"../Utility/CsvLoader.h"
#include<vector>
namespace {
	const char* const kCollisionDataPath = "CollisionParam";
	constexpr int kInitCollisionNum = 100;
}
CollisionDataManager& CollisionDataManager::GetInstance()
{
	static CollisionDataManager collisionDataManager;
	return collisionDataManager;
}

CollisionDataManager::CollisionDataManager()
{
	Load();
}

void CollisionDataManager::Load()
{
	// 一旦読み込む
	std::vector<CollisionParam>collisions = Data::Csv::LoadCsvAs<CollisionParam>(kCollisionDataPath);
	// 要素の確保数を求める
	int reserveNum = collisions[collisions.size() - 1].ID+1;
	// あらかじめ要素を確保
	m_addCollisions.reserve(reserveNum);
	for (int i = 0; i < reserveNum; i++) {
		m_addCollisions.emplace_back(CollisionParam());
	}

	// IDと同じ番号の場所に格納する
	for (auto& collision : collisions) {
		m_addCollisions[collision.ID] = collision;
	}
}

CollisionParam CollisionDataManager::GetCollisionData(int ID)
{
	// 配列の範囲外ならnullptrを返す
	CollisionParam param;
	if (ID < 0 || ID >= m_addCollisions.size())return param;
	param = m_addCollisions[ID];
	return param;
}


void CollisionDataManager::End()
{
}
