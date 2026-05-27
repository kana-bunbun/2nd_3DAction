#include "Player.h"
#include<DxLib.h>
#include<string>
#include"../Animation.h"
#include"../../../Utility/Input.h"
#include"../../../Camera/Camera.h"
#include"../AnimatioController.h"
#include"../CharacterMove.h"
namespace {
	const char* const kModelPath = "Resource\\Player\\ChaWitch\\ChaWitchMesh.mv1";
	const char* const kAnimPath[static_cast<int>(Status::Player::Max)] = {
		"Resource\\Player\\ChaWitch\\Motions\\Idle.mv1",
		"Resource\\Player\\ChaWitch\\Motions\\Walk.mv1",
		"Resource\\Player\\ChaWitch\\Motions\\Parry.mv1",
		"Resource\\Player\\ChaWitch\\Motions\\Damage.mv1",
		"Resource\\Player\\ChaWitch\\Motions\\Dead.mv1",
	};
	// 各アニメーションのループフラグ
	constexpr bool kLoopFrag[static_cast<int>(Status::Player::Max)] = {
		true,  	// アイドル
		true,	// 歩き
		false,	// パリィ
		false,	// ダメージ
		false	// 死亡
	};
	// 各アニメーションの割り込み再生フラグ
	constexpr bool kForcePlay[static_cast<int>(Status::Player::Max)] = {
		false, 	// アイドル
		false,	// 歩き
		false,	// パリィ
		true, 	// ダメージ
		true  	// 死亡
	};
	// プレイヤーの回転の補間割合
	constexpr float kLerpModelRadian = 0.1f;
	// プレイヤーの移動速度
	constexpr float kMoveSpeed = 12;
}

Player::Player() :
	m_animation(),
	m_animData(),
	m_status(),
	m_pCamera(nullptr),
	m_animHandle(),
	m_desireRad(0),
	m_move()
{
	m_modelHandle = MV1LoadModel(kModelPath);
	m_transform.Reset();
	m_transform.position.x = 100;
	m_move.SetLerpSpeed(kLerpModelRadian);
}

Player::~Player()
{
	// アニメーションハンドルの破棄
	for (int& anim : m_animHandle)
		MV1DeleteModel(anim);
	// カメラのポインタを破棄
	if (m_pCamera) {
		m_pCamera = nullptr;
		delete m_pCamera;
	}
}

void Player::Init()
{
	// アニメーションの初期化
	m_animation.Init(GameObject::m_modelHandle);
	// プレイヤーの状態の数だけ繰り返し
	for (int i = 0; i < static_cast<int>(Status::Player::Max); i++) {
		// アニメーションハンドルの初期化
		m_animHandle[i] = -1;
		// アニメーションの更読み込み
		m_animHandle[i] = MV1LoadModel(kAnimPath[i]);
		// 読み込みができたら
		if (m_animHandle[i] ==-1)continue;
		// アニメーションを追加
		m_animation.AddAnim(m_animHandle[i],i);
		// インデックスを設定
		m_animData[i].index = i;
	}

	// アニメーションデータの初期化処理
	for (int i = 0; i < static_cast<int>(Status::Player::Max); i++) {
		// アニメーションデータのループフラグを設定
		m_animData[i].isLoop = kLoopFrag[i];
		// アニメーションデータの割り込み不可能フラグを設定
		m_animData[i].isForcePlay = kForcePlay[i];
	}
	
	// 待機アニメーションを再生
	m_status = Status::Player::Walk;
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);

}

void Player::Update()
{
	// 入力量を取得
	float analogAmount = Input::PadAnalogAmount(Input::Joystick::Left, Pad::Player::P1);
	// 入力角度を取得
	float analogAngle= Input::AnalogAngle(Input::Joystick::Left, Pad::Player::P1);
	// 角度をラジアン角に変更
	analogAngle *= MyMath::ToRadian;
	// カメラの角度で回転するように
	if (m_pCamera)
		analogAngle += m_pCamera->GetHRadian();
	m_status = Status::Player::Neutral;
	
	// 移動速度を0で初期化
	m_move.SetSpeed(0);
	// 移動の入力が行われていたら
	m_move.SetDesireRad(m_transform.rotation.y);
	if (analogAmount != 0) {
		// 移動ステータスに変更
		m_status = Status::Player::Walk;
		// 入力角度まで補間するように
		m_move.SetDesireRad(analogAngle);
		// 移動速度を設定
		m_move.SetSpeed(analogAmount * kMoveSpeed);
	}
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);
	// アニメーションの更新
	m_animation.Update();
	// アニメーションの更デバッグ表示
	m_animation.Debug();
	printfDx("analogAmount : %f\n", analogAmount);
	printfDx("m_desireRad : %f\n", m_desireRad);
	printfDx("m_desireRad : %f\n", m_desireRad * MyMath::ToDegree);

	// 移動をする
	m_move.Update();
	Transform transform = m_move.GetTransform();
	m_transform.position = transform.position;
	m_transform.rotation = transform.rotation;
}

void Player::ResolveCollision(const Collision::Result& result)
{

}

