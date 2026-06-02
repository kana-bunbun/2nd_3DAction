#include "Dragon.h"
#include<string>
namespace {
	const char* const kFilePath="Resource\\Dragon\\ChaDragon\\";
	const char* const kModelPath = "Model.mv1";
	const char* const kMotionPath = "Motions\\";
	const char* const kAnimPath[static_cast<int>(Status::Dragon::Max)] = {
		 "Idle.mv1",
		 "Move.mv1",
		 "Attack.mv1",
		 "Damage.mv1",
		 "Death.mv1",
	};
	constexpr bool kLoopFrag[static_cast<int>(Status::Dragon::Max)]{
		true,
		true,
		true,
		true,
		true,
	};
	constexpr bool kForcePlay[static_cast<int>(Status::Dragon::Max)]{
		true,
		true,
		true,
		true,
		true,
	};
	constexpr Vector3 kModelScale = { 0.7f,0.7f,0.7f };
}
Dragon::Dragon()
{
	m_transform.Reset();

	std::string path = kFilePath;
	m_modelHandle = MV1LoadModel((path+kModelPath).c_str());
	MV1SetScale(m_modelHandle, kModelScale.ToVECTOR());
	m_animation.Init(m_modelHandle);
	path += kMotionPath;
	for (int i = 0; i < static_cast<int>(Status::Dragon::Max);i++) {

		// ファイルパスを組み立てる
		// アニメーションハンドルの初期化
		m_animHandle[i] = -1;

		// アニメーションの更読み込み
		m_animHandle[i] = MV1LoadModel((path+kAnimPath[i]).c_str());
		// 読み込みができたら
		if (m_animHandle[i] == -1)continue;
		// アニメーションを追加
		m_animation.AddAnim(m_animHandle[i], i);
		// インデックスを設定
		m_animData[i].index = i;
	}
}

Dragon::~Dragon()
{
	MV1DeleteModel(m_modelHandle);
}

void Dragon::Init()
{

	// アニメーションデータの初期化処理
	for (int i = 0; i < static_cast<int>(Status::Player::Max); i++) {
		// アニメーションデータのループフラグを設定
		m_animData[i].isLoop = kLoopFrag[i];
		// アニメーションデータの割り込み不可能フラグを設定
		m_animData[i].isForcePlay = kForcePlay[i];
	}

	m_status = Status::Dragon::Walk;
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);
}

void Dragon::Update()
{
	m_animation.Update();

	printfDx("デバッグ\n");
	m_animation.Debug();


}

void Dragon::ResolveCollision(GameObject & other, const Collision::Result & result)
{}

void Dragon::Call(const Vector3 & target)
{}
