#pragma once
#include"../../Component/Transform.h"
#include"../../GameObject.h"

class DragonBreath:public GameObject
{
public:
	DragonBreath();
	~DragonBreath();
	void Init()override;
	void Setup(const Vector3& RegistPos, const Vector3& moveVec);
	void Update(float deltaTime)override;
	void Draw()override;
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	)override;

private:
	Vector3 m_moveVec;		// 移動方向のベクトル
	float m_lifeCount;		// 生存カウント
};

