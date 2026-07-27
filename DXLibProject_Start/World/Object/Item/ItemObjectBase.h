#pragma once
#include"../../GameObject.h"
#include"../../GameObjectParam.h"
class ActionEffectBase;
class ItemObjectBase :public GameObject
{
public:
	/// <summary>
	/// 使用時の初期化処理
	/// </summary>
	virtual void Setup(const Transform& transform) {}
	virtual void InitCollision() {}
	/// <summary>
	/// 回転速度をランダムに求める
	/// </summary>
	virtual void RandomRotate();
	/// <summary>
	/// 効果発動状態にする処理
	/// </summary>
	virtual void EffectSetup() {}
	/// <summary>
	/// 効果発動前の更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void BeforeEffectUpdate(float deltaTime){}
	/// <summary>
	/// 効果発動中の更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void EffectUpdate(float deltaTime){}
protected:
	// 移動方向
	Vector3 m_moveVector;
	// 回転速度
	Vector3 m_rotateSpeed;
	/// <summary>
	/// 効果発動の全体時間
	/// </summary>
	float m_effectCount;
	/// <summary>
	/// 効果発動カウント
	/// </summary>
	float m_activationCount;
	/// <summary>
	/// 当たり判定のパラメータ
	/// </summary>
	CollisionParam m_collisionParam;


};

