#include "CollisionDataManager.h"
#include"../World/GameObjectParam.h"
#include"../Utility/Loder/Data.h"
#include"../Utility/Loder/CsvLoader.h"
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
	// 読み込む
	m_addCollisions = Data::Csv::LoadCsvAs<CollisionParam>(kCollisionDataPath);
}

CollisionParam CollisionDataManager::GetCollisionData(int ID)
{
	// 配列の範囲外かどうかチェック
	CollisionParam param;
	if (ID < 0)return param;
	for (auto& collisionData : m_addCollisions) {
		if (collisionData.ID != ID)continue;
		param = collisionData;
		break;
	}
	return param;
}


void CollisionDataManager::End()
{
}
