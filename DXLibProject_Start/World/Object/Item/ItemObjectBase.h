#pragma once
#include"../../GameObject.h"
#include"../../GameObjectParam.h"
#include"../../../Data/ActionParam.h"
#include"../../../Data/ActionIntervalParam.h"
#include"../../../Data/ActionEffectParam.h"
#include"../../Action/ActionInterval.h"
#include"../../Component/Collision.h"
#include"../../../World/Action/ActionEffectBase.h"
class ItemObjectBase :public GameObject
{
public:
	/// <summary>
	/// 使用時の初期化処理
	/// </summary>
	virtual void Setup(const Transform& transform) {}
	virtual void InitParameter() {}
	/// <summary>
	/// 回転速度をランダムに求める
	/// </summary>
	virtual void RandomRotate();
	/// <summary>
	/// 効果発動状態にする処理
	/// </summary>
	virtual void EffectSetup() {}
	/// <summary>
	/// オブジェクト本体の更新処理
	/// </summary>
	virtual void UpdateObject(float deltaTime){}
	/// <summary>
	/// 効果の発動インターバルの更新処理
	/// </summary>
	virtual void IntervalUpdate(float deltaTime);
	/// <summary>
	/// 発動効果の更新処理
	/// </summary>
	virtual void UpdateEffect(float deltaTime){}
	/// <summary>
	/// 使用中かどうか取得
	/// </summary>
	virtual bool IsUsing() { return false; }
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
	/// 発動効果のパラメータ
	/// </summary>
	ActionParam m_actionParam;
	/// <summary>
	/// インターバル更新クラス
	/// </summary>
	std::unique_ptr<ActionInterval> m_pInterval;
	/// <summary>
	/// 自身の効果
	/// </summary>
	std::unique_ptr<ActionEffectBase> m_pActionEffect;
	/// <summary>
	/// 発動効果の当たり判定
	/// </summary>
	std::unique_ptr<Collision::Shape>m_pEffectCollision;
};

