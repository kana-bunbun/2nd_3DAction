#include "Enemy.h"
#include <string>
namespace {
	const char* const kFilePath = "Resource\\Enemy\\Queen\\";
	const char* const kModelPath = "Model.mv1";
	const char* const kMotionPath = "Animation\\";
	const char* const kAnimPath[static_cast<int>(Status::Queen::Max)] =
	{
		"Idle.mv1",
		"Roar.mv1",
		"Run.mv1",
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
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);
}

void Enemy::Init()
{
	m_status = Status::Queen::Neutral;
	// アニメーション再生
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);
}

void Enemy::LoadModel()
{

	std::string path = kFilePath;
	// モデルの読み込み
	m_modelHandle = MV1LoadModel((path + kModelPath).c_str());
	//MV1SetScale(m_modelHandle, Vector3(kModelScale, kModelScale, kModelScale).ToVECTOR());
	m_animation.Init(m_modelHandle);
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
		m_animation.AddAnim(m_animHandle[i], i);
		// インデックスを設定
		m_animData[i].index = i;
	}

	// アニメーション初期化
	//m_animation.Init(m_modelHandle);

	// アニメーションデータの初期化処理
	for (int i = 0; i < static_cast<int>(Status::Queen::Max); i++) {
		// アニメーションデータのループフラグを設定
		m_animData[i].isLoop = kLoopFrag[i];
		// アニメーションデータの割り込み不可能フラグを設定
		m_animData[i].isForcePlay = kForcePlay[i];
	}


}

void Enemy::Update()
{
	// アニメーション速度を初期化
	m_animation.SetAnimSpeed();


	m_animation.Update();
	m_animation.Debug();
}

void Enemy::ResolveCollision(GameObject& other, const Collision::Result & result)
{}

void Enemy::SetTarget(GameObject* target)
{
	m_target = target;
}
