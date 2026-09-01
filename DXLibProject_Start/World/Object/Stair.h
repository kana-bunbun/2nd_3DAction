#pragma once
#include"../GameObject.h"

/// <summary>
/// 階段オブジェクトの処理を行う
/// </summary>
class Stair:public GameObject
{
public:
	Stair();
	~Stair();

	void Init()override;
	void Update(float deltaTime, const InputData& inputData)override;
	void Draw()override;

	void ResolveCollision(GameObject& other, const Collision::Result& result);
	void ResolveCollision(CollisionTag tag, const Collision::Result& result);
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	void LateDraw()override;
	/// <summary>
	/// 自身の座標を指定したタイルの座標に設定する
	/// </summary>
	/// <param name="tileID">タイルのID</param>
	void SetTile(int tileID);
	void SetBillboardPos(const Vector3& position) { m_billboardPos = position; }
public:
	bool IsHit() { return m_isHitOld; }
private:
	bool m_isHit;
	bool m_isHitOld;
	float m_alpha;
	Vector3 m_billboardPos;
};

