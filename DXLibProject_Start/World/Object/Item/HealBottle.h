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
	void DrawBottle();
	void DrawEffect();
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	)override;


	bool IsTransparent()override { return m_isTrans; }


public:
	// 落下速度
	float m_fallSpeed;
	// 回転速度
	Vector3 m_rotateSpeed;
	// 効果発動中かどうか
	bool m_isEffect;
	// 効果発動時間
	float m_effectCount;
	// 描画の透明度
	float m_alpha;
	// 透明度を扱うかどうか
	bool m_isTrans;
};

