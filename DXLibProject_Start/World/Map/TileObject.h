#pragma once
#include"../GameObject.h"
#include"MapConst.h"
#include<memory>
#include<vector>

class TileObject:public GameObject
{
public:
	TileObject();
	~TileObject();

	void Init()override;
	void End()override;
	void Update(float deltaTime)override;
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;


	void SetFloorModel(int modelHandle) { m_modelHandle=modelHandle; }

protected:
	int m_ID;

};

