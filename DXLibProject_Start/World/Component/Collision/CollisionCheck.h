#pragma once
#include"../../GameObjectParam.h"
#include"../../GameObject.h"
namespace Collision {
	/// <summary>
	/// 当たり判定同士の衝突を調べるべきかどうかを判定
	/// </summary>
	/// <param name="typeA"></param>
	/// <param name="typeB"></param>
	/// <returns>衝突を調べるべきならtrue , そうでなければfalse</returns>
	bool IsCheckCollision(const CollisionType& typeA, const CollisionType& typeB);
	bool IsChebyishevTile(GameObject* baseObj, GameObject* checkObj);
	
}
