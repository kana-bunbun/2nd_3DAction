#include "Player.h"
#include<DxLib.h>
#include<string>
#include"../Animation.h"
#include"../../../Utility/Input.h"
#include"../../../Camera/CameraOld.h"
#include"../AnimatioController.h"
#include"../CharacterMove.h"
#include"../../Object/Barrier.h"
namespace {
	// キャラクターまでのファイルパス
	const char* const kFilePath = "Resource\\Player\\ChaWitch\\";
	// モデルのファイルパス
	const char* const kModelPath = "Model.mv1";
	// モーションファイルまでのファイルパス
	const char* const kMotionPath = "Motions\\";
	// モーションのファイルパス
	const char* const kAnimPath[static_cast<int>(Status::Player::Max)] = {
		"Idle.mv1",
		"Walk.mv1",
		"Parry.mv1",
		"Damage.mv1",
		"Dead.mv1",
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
	// 当たり判定のオフセット
	constexpr Vector3 kCollisionOffset = { 0.0f,30.0f*kModelScale.y,0.0f };
	// 当たり判定の大きさ
	constexpr Vector3 kCollisionSize = { 100.0f,200.0f,100.0f };
	// バリアのオフセット
	constexpr Vector3 kBarrierOffset = { 0.0f,50.0f*kModelScale.y,0.0f };
	// カプセルの半径
	constexpr float kCupsuleRadius = 70;
	// カプセルのオフセット
	constexpr float kCupsuleOffset = 50 * kModelScale.y;
	// カプセルの長さ
	constexpr float kCupsuleLrngth = 30 * kModelScale.y;

}

Player::Player() :
	m_animation(),
	m_animData(),
	m_status(),
	m_pCamera(nullptr),
	m_animHandle(),
	m_speed(0),
	m_desireRad(0),
	m_move(),
	m_parry(false),
	m_pBarrier(nullptr),
	m_dashFlag(false),
	m_gauges()
{
	// ファイルパスを組み立てる
	std::string path = kFilePath;
	path += kModelPath;
	// 組み立てたファイルパスで読みこむ
	m_modelHandle = MV1LoadModel(path.c_str());
	// モデルの大きさを設定
	MV1SetScale(m_modelHandle, kModelScale.ToVECTOR());
	m_transform.Reset();
	m_move.SetLerpSpeed(kLerpModelRadian);
	//m_barrier = std::make_unique<Barrier>(kCollisionOffset);
	m_cupsule = Collision::Cupsule(m_transform, kCupsuleRadius, kCupsuleLrngth);
	m_cupsule.SetOffset(kCupsuleOffset);

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
	if (m_pBarrier) {
		m_pBarrier = nullptr;
		delete m_pBarrier;
	}
}

void Player::Init()
{
	// アニメーションの初期化
	m_animation.Init(GameObject::m_modelHandle);
	std::string path=kFilePath;
	// プレイヤーの状態の数だけ繰り返し
	for (int i = 0; i < static_cast<int>(Status::Player::Max); i++) {
		path = kFilePath;
		path += kMotionPath;
		path += kAnimPath[i];
		// アニメーションハンドルの初期化
		m_animHandle[i] = -1;
		// アニメーションの更読み込み
		m_animHandle[i] = MV1LoadModel(path.c_str());
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
	GameObject::m_collisionTag = CollisionTag::Player;
}

void Player::Update()
{

	m_animation.SetAnimSpeed(1);
	
	float radius = 60;
	Vector3 topPos = m_transform.position+Vector3(0.0f,120.0f*kModelScale.y-radius,0.0f);
	Vector3 bottomPos = m_transform.position + Vector3(0.0f, radius, 0.0f);
	unsigned int color = GetColor(0, 255, 0);
	//DrawCapsule3D(topPos.ToVECTOR(), bottomPos.ToVECTOR(), radius, 10, color, color, FALSE);
	if (GameObject::m_collision)GameObject::m_collision->SetPosition(GetCollisionCenterPos());
	m_collision->DebugDraw();
	m_cupsule.SetTransform(m_transform);


	if (m_pBarrier) {
	m_pBarrier->SetPosition(m_transform.position);
	}
	
	switch (m_status)
	{
	case Status::Player::Neutral:
		break;
	case Status::Player::Walk: {

		if (Input::IsPressed(Input::Button::LThumb, Pad::Player::P1)) {

			m_dashFlag ^= 1;
		}
		float speed = m_speed / kMoveSpeed;
		speed = MyMath::Clamp(speed, 0.0f, 1.3f);
		m_animation.SetAnimSpeed(speed);
		break;
	}
	case Status::Player::Parry:
		Parry();
		break;
	case Status::Player::Damage:
		break;
	case Status::Player::Dead:
		break;
	case Status::Player::Max:
		break;
	default:
		break;
	}
	if(m_status != Status::Player::Walk)
	m_dashFlag = false;
	if (m_status!=Status::Player::Parry)
		m_parry = false;

	UpdateTransform();
	UpdateAnimation();

	printfDx("animSpeed : %f\n", m_animation.GetAnimSpeed());


	m_cupsule.SetTransform(m_transform);
	if (Input::IsDown(Input::Button::Up, Pad::Player::P1)) {
		m_transform.rotation.x += 0.01f;
	}
	if (Input::IsDown(Input::Button::Down, Pad::Player::P1)) {
		m_transform.rotation.x -= 0.01f;
	}
	m_move.SetTransform(m_transform);
	m_cupsule.DebugDraw();
}

void Player::Parry()
{
	float kStopTime = 14.5f;
	m_animation.SetAnimSpeed(1.3f);
	if (m_parry)return;
	if (Input::IsReleased(Input::Button::A, Pad::Player::P1)) {
		m_animation.ResetPlayCount(kStopTime);
		m_parry = true;
		m_pBarrier->Init();
	}
	if (Input::IsDown(Input::Button::A, Pad::Player::P1)) {
		m_parry = false;
		float animSpeed = 1 * (kStopTime - m_animation.GetPlayCount()) / kStopTime;
		m_animation.SetAnimSpeed(animSpeed);
		if (m_animation.GetPlayCount() > kStopTime)
			m_animation.ResetPlayCount(kStopTime);
	}
	else {
	}
}

void Player::ResolveCollision(GameObject& other, const Collision::Result& result)
{
	if (!result.isHit)return;


	switch (other.GetCollisionTag())
	{
	case GameObject::CollisionTag::None:
		break;
	case GameObject::CollisionTag::Player:
		break;
	case GameObject::CollisionTag::Enemy:
	{
		// 押し戻し量を保存
		Vector3 pendingPush = result.normal * result.penetration;
		m_move.AddPendingPush(pendingPush);
		break;
	}
	case GameObject::CollisionTag::Wall:
	{
		// 押し戻しベクトルを生成
		Vector3 revertVec = result.normal * result.penetration;
		// 座標を補正
		m_transform.position += revertVec;
		m_move.SetTransform(m_transform);
		// 衝突判定の更新
		if (GameObject::m_collision)GameObject::m_collision->SetPosition(GetCollisionCenterPos());
		break;
	}
	case GameObject::CollisionTag::Barrier:
		break;
	default:
		break;
	}
	m_cupsule.SetTransform(m_transform);


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
	// スピードが一定以下になったら0にする
	if (m_speed < MyMath::Epsilon)m_speed = 0;
	// 移動の入力が行われていたら
	m_move.SetDesireRad(m_transform.rotation.y);
	// 移動の入力がされていて、かつ歩き状態時のみ移動
	if (analogAmount && m_status == Status::Player::Walk) {
		// 入力角度まで補間するように
		m_move.SetDesireRad(analogAngle);
		// 入力量だけ移動速度を設定
		m_speed = analogAmount * kMoveSpeed*(1+m_dashFlag*1.5f);
	}
	// 移動速度を設定
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
	if (m_status == Status::Player::Parry || (Input::IsPressed(Input::Button::A, Pad::Player::P1))) {
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
	return m_transform.position + kCollisionOffset;
}

void Player::SetBarrier(Barrier* barrier)
{
	m_pBarrier = barrier;
	m_pBarrier->SetOffset(kBarrierOffset);
}

