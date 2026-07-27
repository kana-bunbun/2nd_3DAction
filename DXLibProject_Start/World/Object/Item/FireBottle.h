#pragma once
#include "ItemObjectBase.h"
class FireBottle :public ItemObjectBase
{
public:
	FireBottle();
	~FireBottle();

	void Init()override;
	void InitCollision()override;
	void Update(float deltaTime)override;
	void End()override;
	void Draw()override;
	void DrawEffect();
	void DrawModel();
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	)override;
	void Setup(const Transform& transform)override;
	void EffectSetup()override;
	void BeforeEffectUpdate(float deltaTime)override;
	void EffectUpdate(float deltaTime)override;
private:

	/// <summary>
	/// 透明度を扱うかどうか
	/// </summary>
	float m_alpha;
};

