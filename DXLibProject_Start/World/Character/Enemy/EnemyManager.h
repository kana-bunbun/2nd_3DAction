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
	void Update(float deltaTime);
	void Draw();
	void CreateEnemy(const Transform& createTransform=Transform());
	void SetTarget(GameObject* target);
	void RegistRandomPos();
public:
	Enemy* GetEnemy(int num = 0);
private:

	std::vector <std::unique_ptr<Enemy>>m_enemys;

};

