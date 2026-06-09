#pragma once
#include"../../GameObject.h"
#include<vector>
#include<memory>
class Enemy;
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void End();
	void Update();
	void Draw();
	void CreateEnemy(const Transform& createTransform=Transform());
	void SetTarget(GameObject* target);
private:

	std::vector <std::unique_ptr<Enemy>>m_enemys;

};

