#pragma once
#include"../GameObject.h"
#include"../../Utility/Input.h"
/// <summary>
/// 階段オブジェクトの処理を行う
/// </summary>
class Stair:public GameObject
{
public:
	Stair();
	~Stair();

	void Init()override;
	void Update(float deltaTime)override;
	void Draw()override;

	void ResolveCollision(GameObject& other, const Collision::Result& result);
	void ResolveCollision(GameObject::CollisionTag tag, const Collision::Result& result);
	void SetIsHit(bool isHit) { m_isHit = isHit; }
	/// <summary>
	/// 自身の座標を指定したタイルの座標に設定する
	/// </summary>
	/// <param name="tileID">タイルのID</param>
	void SetTile(int tileID);
	void SetBillboardPos(const Vector3& position) { m_billboardPos = position; }
private:
	bool m_isHit;
	float m_alpha;
	Input::Pad m_pad;
	Vector3 m_billboardPos;
};

