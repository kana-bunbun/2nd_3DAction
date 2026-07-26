#pragma once
#include"../World/GameObjectParam.h"
class CollisionDataManager
{
public:
	static CollisionDataManager& GetInstance();
private:

	CollisionDataManager();
	~CollisionDataManager()=default;

	void Load();
	void GetCollisionData(AddCollisionData data);
public:
	void Delete();
private:
	CollisionDataManager(const CollisionDataManager&) = delete;
	CollisionDataManager& operator =(const CollisionDataManager&) = delete;
	CollisionDataManager(CollisionDataManager&&) = delete;
	CollisionDataManager& operator =(const CollisionDataManager&&) = delete;
private:
	template <class T>
	T GetAddCollisionData(int index);
};

template<class T>
inline T CollisionDataManager::GetAddCollisionData(int index)
{
	return T();
}
