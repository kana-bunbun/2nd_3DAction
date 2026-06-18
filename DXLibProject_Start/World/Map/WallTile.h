#pragma once
#include "TileObject.h"
#include "MapConst.h"
#include<vector>
class WallTile :public TileObject
{
public:
	WallTile(int ID, Vector3 position);
	~WallTile();

	void ResolveCollision(GameObject& other, const Collision::Result& result);
	void Draw()override;
	void SetWallHandle(int wallHandle);
private:
	void RegistWallPos(MapConst::eDirectionFour direction);
private:
	// 隣接する壁の方向
	std::vector<MapConst::eDirectionFour>m_wallDirection;
	std::vector<Transform>m_wallPos;
	// 壁のモデルハンドル
	int m_wallHandle;
};

