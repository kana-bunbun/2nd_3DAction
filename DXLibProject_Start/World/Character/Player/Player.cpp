#include "Player.h"
#include<DxLib.h>
#include<string>
#include<vector>
#include"../Animation.h"
#include"../../../Utility/Input.h"
#include"../../../Camera/CameraOld.h"
#include"../AnimatioController.h"
#include"../CharacterMove.h"
#include"../../Object/Barrier.h"
#include"../../../Utility/CsvLoader.h"
namespace {
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
	// ダッシュ時のアニメーションの再生速度の上限
	constexpr float kRunAnimSpeed = 1.3f;
	// パリィ時のアニメーションの再生速度
	constexpr float kParryAnimSpeed = 1.3f;
	// パリィ時のアニメーションの停止時間
	constexpr float kParryStopTime = 14.5f;
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
	constexpr float kCapsuleRadius = 70;
	// カプセルのオフセット
	constexpr float kCapsuleOffset = 55 * kModelScale.y;
	// カプセルの長さ
	constexpr float kCapsuleLength = 20 * kModelScale.y;

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
	// モデルの設定
	LoadModel();
	// トランスフォームの初期化処理
	m_transform.Reset();
	// 移動時の角度の補間割合を設定
	m_move.SetLerpSpeed(kLerpModelRadian);
	//m_barrier = std::make_unique<Barrier>(kCollisionOffset);
	// カプセルの初期化
	m_capsule = Collision::Capsule(m_transform, kCapsuleRadius, kCapsuleLength);
	// カプセルのオフセットを計算
	m_capsule.SetOffset(kCapsuleOffset);
	// ゲージの初期化
	for (int i = 0; i < GaugeType::Max; i++) {
		m_gauges[i] = std::make_unique<Gauge>();
	}


	
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
	// バリアのポインタを破棄
	if (m_pBarrier) {
		m_pBarrier = nullptr;
		delete m_pBarrier;
	}

}

void Player::Init()
{
	// アニメーションの初期化
	m_animation.Init(GameObject::m_modelHandle);
	
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
	// AABBの初期化
	m_collision = std::make_unique<Collision::AABB>(
		kCollisionOffset,
		kCollisionSize
	);
	// タグをプレイヤーに設定
	GameObject::m_collisionTag = CollisionTag::Player;


	

}

void Player::LoadModel()
{
	// アニメーションの初期化
	m_animation.Init(GameObject::m_modelHandle);
	CsvLoader csv("PlayerModelPath.csv");
	std::vector<std::vector<std::string>>path;
	path = csv.GetLoadData();
	// 組み立てたファイルパスで読みこむ
	std::string str = (path[1][0] + path[3][0]);
	//str = kFilePath;
	//str += kModelPath;
	m_modelHandle = MV1LoadModel(str.c_str());
	// モデルの大きさを設定
	MV1SetScale(m_modelHandle, kModelScale.ToVECTOR());
	for (int i = 0; i < static_cast<int>(Status::Player::Max); i++) {
		// ファイルパスを組み立てる
		// アニメーションハンドルの初期化
		m_animHandle[i] = -1;
		str = (path[1][0] + path[1][1] + path[5][i]);

		// アニメーションの更読み込み
		m_animHandle[i] = MV1LoadModel(str.c_str());
		// 読み込みができたら
		if (m_animHandle[i] == -1)continue;
		// アニメーションを追加
		m_animation.AddAnim(m_animHandle[i], i);
		// インデックスを設定
		m_animData[i].index = i;
	}

	// プレイヤーモデルのエミッシブカラーをCSVデータから読み込んで設定する
	csv=CsvLoader("PlayerEmiColor.csv");
	// 値を格納する配列
	std::vector<float> emiColor;
	for (int i = 0; i < csv.GetLoadData().size(); i++) {
		// csvのB列の値を使う
		float color = std::stof(csv.GetLoadData()[i][1]);
		emiColor.push_back(color);
	}
	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { emiColor[0],emiColor[1],emiColor[2],emiColor[3] };
	MV1SetMaterialEmiColor(m_modelHandle, 0, color);
}

void Player::Update()
{
	// アニメーションの速度を1倍で設定
	m_animation.SetAnimSpeed(1);
	// 当たり判定の中心座標を設定
	if (GameObject::m_collision)GameObject::m_collision->SetPosition(GetCollisionCenterPos());
	// カプセルの中心座標を設定
	m_capsule.SetTransform(m_transform);

	// ステータスに応じた更新処理
	UpdateAction();
	// フラグの更新
	UpdateFlag();
	// トランスフォームの更新
	UpdateTransform();
	// アニメーションの更新
	UpdateAnimation();

	// バリアの座標を設定
	if (m_pBarrier) {
		m_pBarrier->SetPosition(m_transform.position);
	}
	// 当たり判定のデバッグ表示
	m_collision->DebugDraw();
	// カプセルのデバッグ表示
	m_capsule.DebugDraw();

	// デバッグ処理================================================
	if (Input::IsDown(Input::Button::Up, Pad::Player::P1)) {
		m_transform.rotation.x += 0.01f;
	}
	if (Input::IsDown(Input::Button::Down, Pad::Player::P1)) {
		m_transform.rotation.x -= 0.01f;
	}
	m_move.SetTransform(m_transform);
	// デバッグ処理================================================

	float value = 1;
	if (Input::IsDown(Input::Button::LB, Pad::Player::P1))
		for (auto& gauge : m_gauges)
			gauge->Increase(value);
	else if(Input::IsDown(Input::Button::RB,Pad::Player::P1))
		for (auto& gauge : m_gauges)
			gauge->Decrease(value);

	for (auto& gauge : m_gauges) {
		gauge->Clamp();
		printfDx("ゲージ量 : %f\n", gauge->GetValue());
		printfDx("ゲージ最大量 : %f\n", gauge->GetMax());
		printfDx("ゲージ割合 : %f\n", gauge->GetRate());
	}
	m_gauges[GaugeType::MP]->Increase(0.01f);
}

void Player::UpdateAction()
{
	// ステータスによって行動を分岐
	switch (m_status)
	{
	case Status::Player::Neutral:
		break;
	case Status::Player::Walk: {
		// 歩き状態の時にボタンを押すとダッシュ
		if (Input::IsPressed(Input::Button::LThumb, Pad::Player::P1)) {
			m_dashFlag ^= 1;
		}
		// 移動速度の速さに応じてアニメーションの再生速度を計算
		float speed = m_speed / kMoveSpeed;
		speed = MyMath::Clamp(speed, 0.0f, kRunAnimSpeed);
		m_animation.SetAnimSpeed(speed);
		break;
	}
	case Status::Player::Parry:
		// パリィ時の更新処理
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
}
void Player::Parry()
{
	// パリィ時のアニメーションの再生速度を設定
	m_animation.SetAnimSpeed(kParryAnimSpeed);
	if (m_parry)return;
	// ボタンを離した瞬間
	if (Input::IsReleased(Input::Button::A, Pad::Player::P1)) {
		// アニメーションの再生カウントを設定
		m_animation.ResetPlayCount(kParryStopTime);
		// フラグをtrueに
		m_parry = true;
		// バリアの開始
		m_pBarrier->Init();
	}
	// 押している間
	if (Input::IsDown(Input::Button::A, Pad::Player::P1)) {
		// フラグをfalseに
		m_parry = false;
		// アニメーションの再生速度を計算し一定カウントを越さないようにする
		float animSpeed = (kParryStopTime - m_animation.GetPlayCount()) / kParryStopTime;
		// アニメーションの再生速度を設定
		m_animation.SetAnimSpeed(animSpeed);
		m_gauges[GaugeType::MP]->Decrease(0.05f);
		// アニメーションのカウントが一定以上いかないようにする(一応)
		if (m_animation.GetPlayCount() > kParryStopTime)
			m_animation.ResetPlayCount(kParryStopTime);
	}
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

	// 移動をする
	m_move.Update();

	// トランスフォームを更新
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
	// パリィ時またはボタンを押した瞬間
	if (m_status == Status::Player::Parry || (Input::IsPressed(Input::Button::A, Pad::Player::P1))) {
		// パリィ状態に
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

void Player::UpdateFlag()
{
	// ステータスに応じたフラグの更新
	if (m_status != Status::Player::Walk)
		m_dashFlag = false;
	if (m_status != Status::Player::Parry)
		m_parry = false;
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
	// 当たり判定のトランスフォームを更新
	m_capsule.SetTransform(m_transform);


}

Vector3 Player::GetCollisionCenterPos()
{
	return m_transform.position + kCollisionOffset;
}

void Player::SetBarrier(Barrier* barrier)
{
	m_pBarrier = barrier;
	// バリアのオフセットを設定
	m_pBarrier->SetOffset(kBarrierOffset);
}

