#include "Enemy.h"
#include <string>
namespace {
	const char* const kFilePath = "Resource\\Enemy\\Queen\\";
	const char* const kModelPath = "Model.mv1";
	const char* const kMotionPath = "Animation\\";
	const char* const kAnimPath[static_cast<int>(Status::Queen::Max)] =
	{
		"Run.mv1",
		"Idle.mv1",
		"Roar.mv1",
		"Walk.mv1",
		"TailAttack.mv1",
		"JumpAttack.mv1",
		"Damage.mv1",
		"Death.mv1",
	}; 
	constexpr bool kLoopFrag[static_cast<int>(Status::Queen::Max)]{
	true,
	true,
	false,
	false,
	false,
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
		true,
	};
	constexpr float kSphereRadius = 48;
	constexpr int kLeftFootIndex = 48;
	constexpr int kRightFootIndex = 58;

	constexpr float kDefaultAnimSpeed = 0.3f;

	constexpr Vector3 kModelScale = { 0.5f,0.5f,0.5f, };
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
	Vector3 FootPos = MV1GetFramePosition(m_modelHandle, kLeftFootIndex);
	AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius), CollisionType::Foot);
	FootPos = MV1GetFramePosition(m_modelHandle, kRightFootIndex);
	AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius), CollisionType::Foot);
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
	Vector3 FootPos = MV1GetFramePosition(m_modelHandle, kLeftFootIndex);
	AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius),CollisionType::Foot);
	FootPos = MV1GetFramePosition(m_modelHandle, kRightFootIndex);
	AddCollision(std::make_unique<Collision::Sphere>(FootPos, kSphereRadius), CollisionType::Foot);
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
	MV1SetScale(m_modelHandle, kModelScale.ToVECTOR());
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
	//printfDx("Queen\n");
	//printfDx("status : %d\n",m_status);
	//m_animation.Debug();
}

void Enemy::UpdateCollision()
{

	Vector3 FootPos = MV1GetFramePosition(m_modelHandle, kLeftFootIndex);
	m_collisions[0].shape->SetPosition(FootPos);
	FootPos = MV1GetFramePosition(m_modelHandle, kRightFootIndex);
	m_collisions[1].shape->SetPosition(FootPos);

}

void Enemy::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{}

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

