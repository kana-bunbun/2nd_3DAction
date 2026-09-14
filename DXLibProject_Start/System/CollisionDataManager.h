#pragma once
#include"../World/GameObjectParam.h"
#include<vector>
#include<memory>
#include<type_traits>
#include"World/Component/Collision/Collision.h"
#include"World/Component/Collision/ICollider.h"

class CollisionDataManager
{
public:
	static CollisionDataManager& GetInstance();
private:

	CollisionDataManager();
	~CollisionDataManager()=default;

	void Load();
public:
	// 指定IDのコリジョンのパラメータを返す
	CollisionParam GetCollisionData(int ID);
	void End();
	std::unique_ptr<Collision::ICollider> GetCollision(int ID);
private:
	CollisionDataManager(const CollisionDataManager&) = delete;
	CollisionDataManager& operator =(const CollisionDataManager&) = delete;
	CollisionDataManager(CollisionDataManager&&) = delete;
	CollisionDataManager& operator =(const CollisionDataManager&&) = delete;
private:
	std::vector<CollisionParam> m_addCollisions;

};
