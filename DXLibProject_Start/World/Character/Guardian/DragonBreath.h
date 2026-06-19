#pragma once
#include"../../Component/Transform.h"

class DragonBreath
{
public:
	DragonBreath();
	~DragonBreath();

	void Init(const Vector3& RegistPos, const Vector3& moveVec);
	void End();
	void Update(float deltaTime);
	void Draw();

	bool IsActive() { return m_isActive; }
private:
	Transform m_transform;	// 自身のトランスフォーム
	Vector3 m_moveVec;		// 移動方向のベクトル
	bool m_isActive;		// アクティブフラグ
	float m_lifeCount;		// 生存カウント
};

