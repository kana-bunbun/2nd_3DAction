#pragma once
#include"../../GameObject.h"
#include"../AnimationController.h"
#include"../../Component/Transform.h"
#include"../Character.h"
class Enemy :public Character
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
	void Update(float deltaTime,const InputData&inputData)override;
	void UpdateBillboard(float deltaTime);
	/// <summary>
	/// 当たり判定の更新処理
	/// </summary>
	void UpdateCollision()override;
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="result"></param>
	void ResolveCollision(
		GameObject& other,
		const CollisionData& myData,
		const CollisionData& otherData,
		const Collision::Result& result
	);
	void LateDraw()override;
	void SetModelHandle(int modelHandle);
	void SetTarget(GameObject* target);
	void UpdateAnimation(float deltaTime);
	void ChangeAnimation(const Status::Queen& status);
	void Setup()override;
public:		// ゲッター・セッター関数
	const Character::Type& GetCharacterType()override { return Character::Type::Enemy; }

private:
	/// <summary>
	/// アニメーションの管理を行う
	/// </summary>
	AnimationController m_animation;
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
	Vector3 m_billboardPos;
	float m_alpha;
	bool m_isHit;
	bool m_isHitOld;
};



