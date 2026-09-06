#include"pch.h"
#include "CollisionDataManager.h"
#include"../World/GameObjectParam.h"
#include"../Utility/Loder/Data.h"
#include"../Utility/Loder/CsvLoader.h"
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

std::unique_ptr<Collision::Shape> CollisionDataManager::GetCollision(int ID)
{
	CollisionParam param = GetCollisionData(ID);
	switch (param.shapeType)
	{
	case CollisionShape::Sphere: {
		std::unique_ptr<Collision::Sphere>sphere=std::make_unique<Collision::Sphere>(param.position,param.radius);
		return sphere;
	}
	case CollisionShape::AABB: {
		std::unique_ptr<Collision::AABB>aabb = std::make_unique<Collision::AABB>(param.position, param.size);
		return aabb;
	}
	default:
		break;
	}
	return nullptr;
}
