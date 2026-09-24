#include "pch.h"
#include "CollisionCheck.h"
#include"../../Map/MapManager.h"

bool Collision::IsCheckCollision(const CollisionType& typeA, const CollisionType& typeB)
{
	switch (typeA)
	{
	case CollisionType::Null:
		return false;
	case CollisionType::Wall:
		if (typeB == CollisionType::Wall)return false;

		break;
	default:
		break;
	}
    return true;
}

bool Collision::IsChebyishevTile(GameObject* baseObj, GameObject* checkObj)
{
	// 2つのオブジェクトのマスIDを取得
	int baseID = baseObj->GetOnTileID();
	int checkID = checkObj->GetOnTileID();

	// 2つのマスIDが隣り合っているかどうかを返す
	bool isChebyshev = MapManager::GetInstance().IsChebyishevTile(baseID, checkID);

	return isChebyshev;
}