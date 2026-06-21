#pragma once
#include"../GameObject.h"
#include"MapConst.h"
#include<memory>
#include<vector>

class TileObject:public GameObject
{
public:
	TileObject() = default;
	TileObject(int ID, Vector3 position, MapConst::eTerrain terrain);
	~TileObject();

	void Init()override;
	void End()override;
	void Update(float deltaTime)override;
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;

	void Draw()override;
	void SetFloorModel(int modelHandle);
	void SetWallHandle(int wallHandle);
	void RegistWallPos(MapConst::eDirectionFour direction);

	void ChangeTile(int ID, Vector3 position, MapConst::eTerrain terrain);
	void CheckWall();
protected:
	// マスのID
	int m_ID;
	// タイルの種類
	MapConst::eTerrain m_terrain;
	// 隣接する壁の方向
	std::vector<MapConst::eDirectionFour>m_wallDirection;
	// 壁を表示する座標
	std::vector<Transform>m_wallPos;
	// 壁のモデルハンドル
	int m_wallHandle;
};

