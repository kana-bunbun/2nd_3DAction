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
private:
	// 隣接する壁の方向
	std::vector<MapConst::eDirectionFour>WallDirection;
	// 壁のモデルハンドル
	std::vector<int> m_wallHandles;
};

