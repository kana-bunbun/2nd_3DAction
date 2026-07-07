#pragma once
#include"ItemObject.h"
class HealBottle:public ItemObject
{
public:
	HealBottle();
	~HealBottle();

	void Init()override;
	void End()override;
	void Setup(const Transform& transform)override;
	void Update(float deltaTime)override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	)override;


	bool IsTransparent()override { return true; }


public:
	// 落下速度
	float m_fallSpeed;
	// 回転速度
	Vector3 m_rotateSpeed;

};

