#pragma once
#include"ActionEffectBase.h"
class ActionEffect_Heal:public ActionEffectBase
{
public:
	ActionEffect_Heal();
	~ActionEffect_Heal();

	void Init()override;
	void End()override;
	void Update(float deltaTime)override;
	void Draw()override;
	void Reset()override;
	void Execute()override;
	void SetCollision(Collision::Shape* collision) { m_collision = collision; }
	void SetCollisionParam(const CollisionParam& param) { m_collisionParam = param; }
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	) {}
	bool IsTransparent() { return m_isTrans; }
public:
	Collision::Shape* m_collision;
	float m_alpha;
	bool m_isTrans;
};

