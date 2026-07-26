#include "CollisionDataManager.h"
#include"../World/GameObjectParam.h"
#include"../Utility/Data.h"
#include"../Utility/CsvLoader.h"
#include<vector>
namespace {
	const char* const kCollisionDataPath = "CollisionDataParam";
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
	//std::vector<AddCollisionData> addCollisions = Data::Csv::LoadCsvAs<AddCollisionData>(kCollisionDataPath);

	//switch (addCollisions[0].type)
	//{
	//default:
	//	break;
	//}

}

void CollisionDataManager::GetCollisionData(AddCollisionData data)
{
	//switch (data.)
	//{
	//default:
	//	break;
	//}
}

void CollisionDataManager::Delete()
{}
