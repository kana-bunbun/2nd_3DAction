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
	void Draw()override;
	void DrawModel();
	void DrawEffect();
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	)override;
	void EffectSetup()override;
	void BeforeEffectUpdate(float deltaTime)override;
	void EffectUpdate(float deltaTime)override;
	bool IsTransparent()override { return m_isTrans; }


public:

	// 描画の透明度
	float m_alpha;
	// 透明度を扱うかどうか
	bool m_isTrans;
};

