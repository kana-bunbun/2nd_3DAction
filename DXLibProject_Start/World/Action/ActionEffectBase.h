#pragma once
#include"../GameObject.h"
#include"../../Data/ActionEffectParam.h"
#include"../Component/Collision.h"

class ActionEffectBase:public GameObject
{
public:
	ActionEffectBase() = default;
	~ActionEffectBase() = default;

	virtual void Reset() = 0;
	virtual void Execute() = 0;
	void SetActionEffectParam(const ActionEffectParam& param) { m_param = param; }

	/// <summary>
	/// 当たり判定を追加できるかどうか
	/// </summary>
	/// <returns>すでに当たり判定があればfalse</returns>
	virtual bool CanAddCollision() { return !m_collisions.size(); }
	void SetPosition(const Vector3& position) { m_transform.position = position; }
protected:
	// 効果のパラメータ
	ActionEffectParam m_param;
	CollisionParam m_collisionParam;
	// 効果発動のインターバルのカウント
	float m_executeCount;
	// 現在の発動時間
	float m_effectCount;
};

