#pragma once
#include"ItemObjectBase.h"
class ActionEffect_Heal;
class HealBottle:public ItemObjectBase
{
public:
	HealBottle();
	~HealBottle();

	void Init()override;
	void InitParameter()override;
	void End()override;
	void Setup(const Transform& transform)override;
	void Update(float deltaTime)override;
	void Draw()override;
	void DrawModel();
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	)override;
	void EffectSetup()override;
	void UpdateObject(float deltaTime)override;
	bool IsUsing()override;
};

