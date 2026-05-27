#pragma once
#include"../Component/Transform.h"
/// <summary>
/// キャラクターの移動をする関数
/// </summary>
class CharacterMove
{
public:
	CharacterMove();
	~CharacterMove();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();
	/// <summary>
	/// 終了処理
	/// </summary>
	void End();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

public:		// ゲッター・セッター関数
	// トランスフォームの取得をする関数
	const Transform GetTransform() { return m_transform; }
	// 保管するための角度を設定する関数
	const void SetDesireRad(float radian) { m_desireRad = radian; }
	// 移動速度を設定する関数
	const void SetSpeed(float speed) { m_speed = speed; }
	// 補間の速度を設定する関数
	const void SetLerpSpeed(float lerp) { m_lerpSpeed = lerp; }
private:
	/// <summary>
	/// トランスフォーム
	/// </summary>
	Transform m_transform;
	/// <summary>
	/// 補間するための角度
	/// </summary>
	float m_desireRad;
	/// <summary>
	/// 移動速度
	/// </summary>
	float m_speed;
	/// <summary>
	/// 角度の補間割合
	/// </summary>
	float m_lerpSpeed;
};

