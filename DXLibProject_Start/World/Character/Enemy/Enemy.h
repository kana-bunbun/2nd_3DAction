#pragma once
#include"../../GameObject.h"
#include"../AnimatioController.h"
#include"../../Component/Transform.h"
class Enemy :public GameObject
{
public:
	Enemy();
	Enemy(const Transform& transform);
	~Enemy();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init()override;
	/// <summary>
	/// モデル読み込み
	/// </summary>
	void LoadModel();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="result"></param>
	void ResolveCollision(GameObject& other, const Collision::Result& result)override;

	void SetModelHandle(int modelHandle);
	void SetTarget(GameObject* target);

public:		// ゲッター・セッター関数
private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimatioController m_animation;
	/// <summary>
	/// アニメーションデータの配列
	/// </summary>
	Status::AnimData m_animData[static_cast<int>(Status::Queen::Max)] = { -1 };
	/// <summary>
	/// 現在のステータス
	/// </summary>
	Status::Queen m_status;
	/// <summary>
	/// アニメーションのハンドル
	/// </summary>
	int m_animHandle[static_cast<int>(Status::Queen::Max)];

	/// <summary>
	/// 角度
	/// </summary>
	float m_desireRad;

	/// <summary>
	/// ターゲット
	/// </summary>
	GameObject* m_target;
};



