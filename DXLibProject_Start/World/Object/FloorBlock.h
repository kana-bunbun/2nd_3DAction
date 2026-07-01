#pragma once
#include "../GameObject.h"
#include "../World/Component/Transform.h"
#include "../Utility/Vector3.h"
#include "../World/Component/Collision.h"
class FloorBlock :public GameObject
{
public:
	FloorBlock();
	~FloorBlock()override = default;

	void Init()override;
	void Update(float deltaTime)override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);

private:
};

