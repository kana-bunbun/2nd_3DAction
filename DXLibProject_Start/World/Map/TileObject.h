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
	void Update(float deltaTime)override;
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;
	void ResolveCollision(GameObject::CollisionTag tag, const Collision::Result& result)override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	void Draw()override;
	void SetFloorModel(int modelHandle);
	void SetWallHandle(int wallHandle);
	void RegistWall(const MapConst::eDirectionFour& direction);

	void ChangeTile(int ID, const Vector3& position, const MapConst::eTerrain& terrain);
	void CheckWall();

	Collision::Result CheckCollision(GameObject* object);
protected:
	// マスのID
	int m_ID;
	// タイルの種類
	MapConst::eTerrain m_terrain;
	// 隣接する壁の方向
	std::array<bool, static_cast<int>(MapConst::eDirectionFour::Max)> m_wallDirection;
	// 壁を表示する座標
	std::vector<Transform>m_wallPos;
	// 壁のモデルハンドル
	int m_wallHandle;
	// 当たり判定の配列
	std::array<std::unique_ptr<Collision::Shape>, static_cast<int>(MapConst::eDirectionFour::Max)>m_collisions;
};

