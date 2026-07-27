#pragma once
#include"ItemObjectBase.h"
class ActionEffect_Heal;
class HealBottle:public ItemObjectBase
{
public:
	HealBottle();
	~HealBottle();

	void Init()override;
	void InitCollision()override;
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
	void BeforeEffectUpdate(float deltaTime)override;
	bool IsTransparent()override { return m_isEffect; }


public:
	// 描画の透明度
	float m_alpha;
	// 透明度を扱うかどうか
	bool m_isEffect;
	/// <summary>
	/// 自身の効果
	/// </summary>
	ActionEffect_Heal* m_actionEffect;
};

