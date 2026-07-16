#include "Bee.h"

#include"../GameObject.h"
#include"Animation.h"
#include"AnimationController.h"

#include<DxLib.h>
#include<cassert>
#include<string>
#include<memory>

#include"../../Utility/Color.h"
#include"../../Utility/MyMath.h"

namespace {
	// モデルのファイルパス
	const char* const kModelPath = "Resource\\testbox.mv1";
	// 初期座標
	constexpr Vector3 kInitPos = { -200,0.0f,0.0f };
	// モデルの大きさ
	constexpr Vector3 kModelScale = { 0.01f,0.01f,0.01f };
	//constexpr Vector3 kModelScale = { 1.0f,1.0f,1.0f };
	// 当たり判定の大きさ
	constexpr Vector3 kCollisionSize = { 170.0f,170.0f,170.0f };
	// 当たり判定の座標
	constexpr Vector3 kModelOffset = { 0.0f,90.0f,0.0f };
	// アニメーションの名前
	const char* const kAnimationName[static_cast<int>(Status::Bee::Max)] = {
		"MonsterArmature|Bite_Front",
		"MonsterArmature|Death",
		"MonsterArmature|Flying",
		"MonsterArmature|HitRecieve",
	};
	// 各アニメーションのループフラグ
	constexpr bool kLoopFrag[static_cast<int>(Status::Bee::Max)] = {
		false, 	// 攻撃
		false,	// 死亡
		true,	// 飛行
		false,	// 被ダメージ
	};
	// 各アニメーションの割り込み再生フラグ
	constexpr bool kForcePlay[static_cast<int>(Status::Bee::Max)] = {
		false, 	// 攻撃
		false,	// 死亡
		true,	// 飛行
		false, 	// 被ダメージ
	};
}


Bee::Bee():
	m_state(Status::Bee::Fly)
{
	GameObject::m_modelHandle = MV1LoadModel(kModelPath);
	m_animation.Init(m_modelHandle);
	for (int i = 0;i < static_cast<int>(Status::Bee::Max);i++) {

		m_animData[i].index = MV1GetAnimIndex(m_modelHandle, kAnimationName[i]);
		// アニメーションデータのループフラグを設定
		m_animData[i].isLoop = kLoopFrag[i];
		// アニメーションデータの割り込み不可能フラグを設定
		m_animData[i].isForcePlay = kForcePlay[i];
	}
	GameObject::m_collisionTag = CollisionTag::Enemy;
}

void Bee::Init()
{
	GameObject::m_transform.position += kInitPos;
	GameObject::m_transform.scale = kModelScale;
	// AABBのコリジョンの生成
	AddCollision(std::make_unique<Collision::AABB>(
		kModelOffset,
		kCollisionSize
	), CollisionType::Body);
	MV1SetScale(m_modelHandle, kModelScale.ToVECTOR());
}

void Bee::Update(float deltaTime)
{

	// アニメーションの更新処理
	UpdateAnimation(deltaTime);
	m_transform.position.z--;

}

void Bee::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{
	// 当たっていなければ即時return
	if (!result.isHit)return;

	// Playerでなければ即時return
	if (other.GetCollisionTag() != CollisionTag::Player)return;

	// 押し戻しベクトルを生成
	Vector3 revertVec = result.normal * result.penetration;

	// 座標を移動
	Vector3 resultPush = m_transform.position + (revertVec * 20.0f);
	SetPosition(resultPush);
	

}

Vector3 Bee::GetCollisionCenterPos() const
{
	return m_transform.position;
}

void Bee::UpdateAnimation(float deltaTime)
{
	// アニメーションの再生
	m_animation.Update(deltaTime);
}

void Bee::ChangeAnimation(Status::Bee next)
{
	// アニメーションの更新
	m_state = next;

	// アニメーションの再生処理
	m_animation.PlayAnimation(m_animData[static_cast<int>(next)]);
}

