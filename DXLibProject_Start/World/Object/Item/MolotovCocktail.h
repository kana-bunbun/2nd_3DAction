#pragma once
#include "ItemObject.h"
class MolotovCocktail :public ItemObject
{
public:
	MolotovCocktail();
	~MolotovCocktail();

	void Init()override;
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
	bool IsTransparent()override { return m_isEffect; }
private:
	/// <summary>
	/// 効果発動中かどうか
	/// </summary>
	bool m_isEffect;
	/// <summary>
	/// 透明度を扱うかどうか
	/// </summary>
	float m_alpha;
	// 効果発動時間
	float m_effectCount;
};

