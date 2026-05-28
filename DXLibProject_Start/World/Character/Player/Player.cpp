#include "Player.h"
#include<DxLib.h>
#include<string>
#include"../Animation.h"
#include"../../../Utility/Input.h"
#include"../../../Camera/Camera.h"
#include"../AnimatioController.h"
#include"../CharacterMove.h"
namespace {
	const char* const kModelPath = "Resource\\Player\\ChaWitch\\Model.mv1";
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
	constexpr float kMoveSpeed = 8;
	// 移動速度の減衰量
	constexpr float kAttenuation = 0.8f;
	// モデルの大きさ
	constexpr Vector3 kModelScale = { 2.0f,2.0f,2.0f };
	constexpr Vector3 kCollisionOffset = { 0.0f,30.0f*kModelScale.y,0.0f };
	constexpr Vector3 kCollisionSize = { 100.0f,200.0f,100.0f };
}

Player::Player() :
	m_animation(),
	m_animData(),
	m_status(),
	m_pCamera(nullptr),
	m_animHandle(),
	m_speed(0),
	m_desireRad(0),
	m_move()
{
	m_modelHandle = MV1LoadModel(kModelPath);
	MV1SetScale(m_modelHandle, kModelScale.ToVECTOR());
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
		if (m_animHandle[i] == -1)continue;
		// アニメーションを追加
		m_animation.AddAnim(m_animHandle[i], i);
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
	m_status = Status::Player::Neutral;
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);

	m_collision = std::make_unique<Collision::AABB>(
		kCollisionOffset,
		kCollisionSize
	);
}

void Player::Update()
{
	UpdateTransform();
	UpdateAnimation();
	float radius = 60;
	Vector3 topPos = m_transform.position+Vector3(0.0f,120.0f*kModelScale.y-radius,0.0f);
	Vector3 bottomPos = m_transform.position + Vector3(0.0f, radius, 0.0f);
	unsigned int color = GetColor(0, 255, 0);
	DrawCapsule3D(topPos.ToVECTOR(), bottomPos.ToVECTOR(), radius, 10, color, color, FALSE);
	if (GameObject::m_collision)GameObject::m_collision->SetPosition(GetCollisionCenterPos());
	m_collision->DebugDraw();
	
}

void Player::ResolveCollision(const Collision::Result& result)
{
	if (!result.isHit)return;

	// 押し戻し量を保存
	Vector3 pendingPush = result.normal * result.penetration*30;
	m_move.AddPendingPush(pendingPush);

	//// 押し戻しベクトルを生成
	//Vector3 revertVec = result.normal * result.penetration;
	//// 座標を補正
	//m_transform.position += revertVec;
	//m_move.SetTransform(m_transform);

	//// 衝突判定の更新
	//if (GameObject::m_collision)GameObject::m_collision->SetPosition(GetCollisionCenterPos());

}

void Player::UpdateTransform()
{
	// 入力量を取得
	float analogAmount = Input::PadAnalogAmount(Input::Joystick::Left, Pad::Player::P1);
	// 入力角度を取得
	float analogAngle = Input::AnalogAngle(Input::Joystick::Left, Pad::Player::P1);
	// 角度をラジアン角に変更
	analogAngle *= MyMath::ToRadian;
	// カメラの角度で回転するように
	if (m_pCamera)
		analogAngle += m_pCamera->GetHRadian();

	// 移動速度を減衰させる
	m_speed *= kAttenuation;
	// 移動の入力が行われていたら
	m_move.SetDesireRad(m_transform.rotation.y);
	if (analogAmount && m_status == Status::Player::Walk) {
		// 入力角度まで補間するように
		m_move.SetDesireRad(analogAngle);
		// 入力量だけ移動速度を設定
		m_speed = analogAmount * kMoveSpeed;
	}
	m_move.SetSpeed(m_speed);


	printfDx("analogAmount : %f\n", analogAmount);
	printfDx("m_desireRad : %f\n", m_desireRad);
	printfDx("m_desireRad : %f\n", m_desireRad * MyMath::ToDegree);

	// 移動をする
	m_move.Update();
	Transform transform = m_move.GetTransform();
	m_transform.position = transform.position;
	m_transform.rotation = transform.rotation;
}

void Player::UpdateAnimation()
{

	// アニメーションの更新
	m_animation.Update();
	// アニメーションのデバッグ表示
	m_animation.Debug();
	// 割り込み再生またはアニメーション再生中なら処理しない
	if (m_animation.IsForcePlay() && m_animation.IsPlaying())return;
	// 次のアニメーションがどれか調べる
	Status::Player nextStatus;
	nextStatus = Status::Player::Neutral;
	// 
	if (m_status == Status::Player::Parry || (Input::IsPressed(Input::Button::Y, Pad::Player::P1))) {
		nextStatus = Status::Player::Parry;
	}
	// 移動の入力があるとき
	else if (Input::PadAnalogAmount(Input::Joystick::Left, Pad::Player::P1)) {
		// 移動ステータスに
		nextStatus = Status::Player::Walk;
	}
	// アニメーションが終了していればアイドル状態に
	if (!m_animation.IsPlaying())
		nextStatus = Status::Player::Neutral;

	// ステータスが異なっていたらアニメーションの変更
	if (m_status != nextStatus) {
		ChangeAnimation(nextStatus);
	}

}

void Player::ChangeAnimation(Status::Player& status)
{
	// アニメーションの時間をリセット
	m_animation.ResetPlayCount();
	// アニメーションを再生
	m_animation.PlayAnimation(m_animData[static_cast<int>(status)]);
	// ステータスの更新
	m_status = status;
}

Vector3 Player::GetCollisionCenterPos()
{
	return m_transform.position+ kCollisionOffset;
}

