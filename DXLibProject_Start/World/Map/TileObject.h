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
	void Draw()override;


private:
	// モデルハンドルの配列
	std::vector<int>m_modelHandles;
	// 壁の描画方向の配列
	std::vector<MapConst::eDirectionFour>m_wallDirections;
};

