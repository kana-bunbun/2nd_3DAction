#pragma once
#include"../../GameObject.h"
#include"../AnimatioController.h"

class Enemy :public GameObject
{
public:
	/// <summary>
	/// プレイヤーのコンストラクタ
	/// </summary>
	Enemy();
	/// <summary>
	/// プレイヤーのデストラクタ
	/// </summary>
	~Enemy();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="result"></param>
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;







public:		// ゲッター・セッター関数
private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimatioController m_animation;
	/// <summary>
	/// アニメーションデータの配列
	/// </summary>
	Status::AnimData m_animData[static_cast<int>(Status::Player::Max)] = { -1 };
	/// <summary>
	/// 現在のステータス
	/// </summary>
	Status::Player m_status;
	/// <summary>
	/// アニメーションのハンドル
	/// </summary>
	int m_animHandle[static_cast<int>(Status::Player::Max)];

	/// <summary>
	/// 角度
	/// </summary>
	float m_desireRad;

};



