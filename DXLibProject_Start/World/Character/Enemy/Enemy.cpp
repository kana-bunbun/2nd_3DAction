#include "Enemy.h"
#include "../../UI/BillboardManager.h"
#include <string>
namespace {
	const char* const kFilePath = "Resource\\Enemy\\Queen\\";
	const char* const kModelPath = "Model.mv1";
	const char* const kMotionPath = "Animation\\";
	const char* const kAnimPath[static_cast<int>(Status::Queen::Max)] =
	{
		"Idle.mv1",
		"Roar.mv1",
		"Walk.mv1",
		"Run.mv1",
		"JumpAttack.mv1",
		"Damage.mv1",
		"Death.mv1",
	};
	constexpr bool kLoopFrag[static_cast<int>(Status::Queen::Max)]{
	true,
	false,
		true,
	true,
	false,
	false,
	false,
	};
	constexpr bool kForcePlay[static_cast<int>(Status::Queen::Max)]{
		false,
		false,
		true,
		true,
		true,
		true,
		true,
	};
	constexpr float kSphereRadius = 480;
	constexpr int kLeftFootIndex = 48;
	constexpr int kRightFootIndex = 58;
	constexpr int kBodyIndex = 2;

	constexpr float kDefaultAnimSpeed = 0.3f;
	constexpr Vector3 kBillboardOffset = { 0.0f,100.0f,0.0f };
	constexpr float kAlphaSpeed = 255.0f * 3.0f;

}

Enemy::Enemy():
	m_animation(),
	m_animData(),
	m_status(),
	m_animHandle(),
	m_desireRad(),
	m_target(nullptr)
{
	m_transform.Reset();

	LoadModel();
	//Vector3 FootPos = MV1GetFramePosition(m_modelHandle, kLeftFootIndex);
	//AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius), CollisionType::Foot);
	//FootPos = MV1GetFramePosition(m_modelHandle, kRightFootIndex);
	//AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius), CollisionType::Foot);
	Vector3 bodyPos = MV1GetFramePosition(m_modelHandle, kBodyIndex);
	AddCollision(std::make_unique<Collision::Sphere>(bodyPos, kSphereRadius), CollisionType::Body);
	m_collisionTag = GameObject::CollisionTag::Enemy;
	m_HPGauge = std::make_unique<Gauge>();
}

Enemy::Enemy(const Transform& transform) :
	m_animation(),
	m_animData(),
	m_status(),
	m_animHandle(),
	m_desireRad(),
	m_target(nullptr)
{
	m_transform = transform;

	LoadModel();
	//Vector3 FootPos = MV1GetFramePosition(m_modelHandle, kLeftFootIndex);
	//AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius), CollisionType::Foot);
	//FootPos = MV1GetFramePosition(m_modelHandle, kRightFootIndex);
	//AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius), CollisionType::Foot);
	Vector3 bodyPos = MV1GetFramePosition(m_modelHandle, kBodyIndex);
	AddCollision(std::make_unique<Collision::Sphere>(bodyPos, kSphereRadius), CollisionType::Body);
	m_collisionTag = GameObject::CollisionTag::Enemy;
	m_HPGauge = std::make_unique<Gauge>();
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);
}

void Enemy::Init()
{
	
}

void Enemy::LoadModel()
{

	std::string path = kFilePath;
	// モデルの読み込み
	m_modelHandle = MV1LoadModel((path + kModelPath).c_str());
	//MV1SetScale(m_modelHandle, Vector3(kModelScale, kModelScale, kModelScale).ToVECTOR());
	//m_animation.Init(m_modelHandle);
	path += kMotionPath;
	for (int i = 0; i < static_cast<int>(Status::Queen::Max); i++) {

		// ファイルパスを組み立てる
		// アニメーションハンドルの初期化
		m_animHandle[i] = -1;

		// アニメーションの更読み込み
		m_animHandle[i] = MV1LoadModel((path + kAnimPath[i]).c_str());
		// 読み込みができたら
		if (m_animHandle[i] == -1)continue;
		// アニメーションを追加
		m_animation.AddAnim(m_animHandle[i]);
		// インデックスを設定
		m_animData[i].index = i;
		// アニメーションデータのループフラグを設定
		m_animData[i].isLoop = kLoopFrag[i];
		// アニメーションデータの割り込み不可能フラグを設定
		m_animData[i].isForcePlay = kForcePlay[i];
	}

	// アニメーション初期化
	m_animation.Init(m_modelHandle);

	m_status = Status::Queen::Neutral;
	// アニメーション再生
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);

}

void Enemy::Update(float deltaTime)
{
	m_animation.SetAnimSpeed(kDefaultAnimSpeed);
	// アニメーション速度を初期化
	UpdateAnimation(deltaTime);

	m_animation.Update(deltaTime);
	printfDx("enemy::HP : %f\n", m_HPGauge->GetValue());
	UpdateBillboard(deltaTime);
}

void Enemy::UpdateBillboard(float deltaTime)
{
	m_isHitOld = m_isHit;
	// アルファ値の増減量を求める
	float alphaValue = kAlphaSpeed * deltaTime;
	if (m_isHitOld) {	// プレイヤーが当たっているときアルファ値増加
		m_alpha += alphaValue;
	}
	else {			// プレイヤーが当たっていないときアルファ値減少
		m_alpha -= alphaValue;
	}
	// アルファ値を値域内に収める
	m_alpha = MyMath::Clamp(m_alpha, 0.0f, 255.0f);
	m_isHit = false;
}

void Enemy::UpdateCollision()
{

	//Vector3 FootPos = MV1GetFramePosition(m_modelHandle, kLeftFootIndex);
	//m_collisions[0].shape->SetPosition(FootPos);
	//FootPos = MV1GetFramePosition(m_modelHandle, kRightFootIndex);
	//m_collisions[1].shape->SetPosition(FootPos);
	Vector3 bodyPos = MV1GetFramePosition(m_modelHandle, kBodyIndex);
	m_collisions[0].shape->SetPosition(bodyPos);
}

void Enemy::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{
	switch (other.GetCollisionTag())
	{
	case GameObject::CollisionTag::Player:
	/*	if (!IsDead()) {
			break;
		}
		else { 
			int t=0;
		}*/
		m_isHit = true;
		m_billboardPos = other.GetTransform().position;
		break;
	default:
		break;
	}
}

void Enemy::LateDraw()
{
	return;
	Vector3 billboardPos = m_billboardPos + kBillboardOffset;
	// 透明度を操作して描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	// ビルボードで描画
	BillboardManager::GetInstance().DrawBillboard(billboardPos, -0.2f, 0, 300, 0, BillboardManager::eBillboard::Collection);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Enemy::SetModelHandle(int modelHandle)
{}

void Enemy::SetTarget(GameObject* target)
{
	m_target = target;
}

void Enemy::UpdateAnimation(float deltaTime)
{
	// アニメーションの更新
	m_animation.Update(deltaTime);
	// アニメーションのデバッグ表示
	//m_animation.Debug();
	// 割り込み再生またはアニメーション再生中なら処理しない
	if (m_animation.IsForcePlay() && m_animation.IsPlaying())return;
	// 次のアニメーションがどれか調べる
	Status::Queen nextStatus;
	nextStatus = Status::Queen::Neutral;
	// アニメーションが終了していればアイドル状態に
	if (!m_animation.IsPlaying())
		nextStatus = Status::Queen::Neutral;
	// HPが0なくなっていたら
	if(!m_HPGauge->GetValue())
		nextStatus = Status::Queen::Dead;
	// ステータスが異なっていたらアニメーションの変更
	if (m_status != nextStatus) {
		ChangeAnimation(nextStatus);
	}
}

void Enemy::ChangeAnimation(const Status::Queen& status)
{
	// アニメーションの時間をリセット
	m_animation.ResetPlayCount();
	// アニメーションを再生
	m_animation.PlayAnimation(m_animData[static_cast<int>(status)]);
	// ステータスの更新
	m_status = status;
}

void Enemy::Setup()
{
	m_HPGauge->SetValue(m_HPGauge->GetMax());
}

