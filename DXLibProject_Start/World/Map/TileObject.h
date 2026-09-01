#pragma once
#include"../GameObject.h"
#include"MapConst.h"
#include<memory>
#include<vector>
#include<array>

class TileObject:public GameObject
{
public:
	TileObject() = default;
	TileObject(int ID, const Vector3& position, const MapConst::eTerrain& terrain);
	~TileObject();

	void Init()override;
	void End()override;
	void Update(float deltaTime,const InputData&inputData)override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	void Draw()override;
	void SetFloorModel(ModelData* modelData);
	void SetWallHandle(ModelData* wallData);
	void RegistWall(const MapConst::eDirectionFour& direction);

	void ChangeTile(int ID, const Vector3& position, const MapConst::eTerrain& terrain);
	void CheckWall();

	void SetIsStair(bool isStair) { m_isStair = isStair; }
protected:
	// マスのID
	int m_ID;
	// タイルの種類
	MapConst::eTerrain m_terrain;
	// 隣接する壁の方向
	std::array<bool, static_cast<int>(MapConst::eDirectionFour::Max)> m_wallDirection;
	// 壁を表示する座標
	std::vector<Transform>m_wallPos;
	// 階段マスかどうか
	bool m_isStair;
	// 壁の当たり判定
	std::vector < std::unique_ptr<Collision::Shape>>m_walls;
	ModelData* m_wallModelData;
};

