#include "Player.h"
#include<DxLib.h>
#include<string>
#include<vector>
#include"../Animation.h"
#include"../../../Utility/Input.h"
#include"../../../Camera/CameraOld.h"
#include"../AnimationController.h"
#include"../CharacterMove.h"
#include"../../Object/Barrier.h"
#include"../../../Utility/CsvLoader.h"
#include"../../../Camera/Camera.h"
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
	constexpr float kLerpModelRadian = 6.0f;
	// プレイヤーの移動速度
	constexpr float kMoveSpeed = 480;
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
	constexpr Vector3 kModelOffset = { 0.0f,30.0f*kModelScale.y,0.0f };
	// 当たり判定の大きさ
	constexpr Vector3 kCollisionSize = { 100.0f,200.0f,100.0f };
	// バリアのオフセット
	constexpr Vector3 kBarrierOffset = { 0.0f,50.0f*kModelScale.y,0.0f };
	// カプセルの半径
	constexpr float kCapsuleRadius = 50;
	// カプセルのオフセット
	constexpr float kCapsuleOffset = 55 * kModelScale.y;
	// カプセルの長さ
	constexpr float kCapsuleLength = 20 * kModelScale.y;

	// 本体コリジョンのデータ
	constexpr float kBodyCollisionOffsetY = 98.0f;
	constexpr Vector3 kBodyCollisionSize = { 78.0f,195.0f,78.0f };

	constexpr int kHeadFrameIndex = 6;
	constexpr int kHatRightFrameIndex = 11;
	constexpr int kHatLeftFrameIndex = 12;
	constexpr int kWaistFrameIndex = 3;

	// パリィ溜め時のMP減少量
	constexpr float kParryMPDecrease = 0.05f;

}

Player::Player(Vector3 position) :
	m_animation(),
	m_animData(),
	m_status(),
	m_animHandle(),
	m_speed(0),
	m_desireRad(0),
	m_move(),
	m_parry(false),
	m_charge(false),
	m_pBarrier(nullptr),
	m_dashFlag(false),
	m_isGroud(true),
	m_isJump(false)
{
	// モデルの設定
	LoadModel();
	// トランスフォームの初期化処理
	m_transform.Reset();
	// 移動時の角度の補間割合を設定
	m_move.SetLerpSpeed(kLerpModelRadian);
	//m_barrier = std::make_unique<Barrier>(kCollisionOffset);
	// カプセルの初期化
	m_capsule = Collision::Capsule(kCapsuleRadius);
	// カプセルのオフセットを計算
	m_capsule.SetOffset(kCapsuleOffset);
	// ゲージの初期化
	m_HPGauge=std::make_unique<Gauge>();
	m_MPGauge=std::make_unique<Gauge>();
	// 当たり判定追加
	AddCollision(std::make_unique<Collision::AABB>(Vector3(0.0f, kBodyCollisionOffsetY, 0.0f), kBodyCollisionSize), CollisionType::Body);
	// 座標設定
	SetPosition(position);
}

Player::~Player()
{
	// アニメーションハンドルの破棄
	for (int& anim : m_animHandle)
		MV1DeleteModel(anim);
	
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

	// タグをプレイヤーに設定
	GameObject::m_collisionTag = CollisionTag::Player;


	

}

void Player::LoadModel()
{
	// csvデータ読み込み
	CsvLoader csv("PlayerModelPath.csv");
	std::vector<std::vector<std::string>>path;
	path = csv.GetLoadData();
	// 組み立てたファイルパスで読みこむ
	std::string str = (path[1][0] + path[3][0]);
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
		m_animation.AddAnim(m_animHandle[i]);
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

void Player::Update(float deltaTime)
{

	// アニメーションの速度を1倍で設定
	m_animation.SetAnimSpeed(1);

	// ステータスに応じた更新処理
	UpdateAction();
	// フラグの更新
	UpdateFlag();
	// トランスフォームの更新
	UpdateTransform(deltaTime);
	// アニメーションの更新
	UpdateAnimation(deltaTime);

	// バリアの座標を設定
	if (m_pBarrier) {
		m_pBarrier->SetPosition(m_transform.position);
	}



	// ゲージが上限・下限を超えないようにする
	

	// MPの自動回復
	if(m_status!=Status::Player::Parry)
	m_MPGauge->Increase(deltaTime);

	//m_animation.Debug();
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
		if (Input::IsPressed(Input::Button::LThumb, m_pad)) {
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
	if ((!Input::IsDown(Input::Button::A, m_pad)&&m_charge) ||
		!m_MPGauge->GetRate()) {
		// アニメーションの再生カウントを設定
		m_animation.ResetPlayCount(kParryStopTime);
		// フラグをtrueに
		m_parry = true;
		// バリアの開始
		m_pBarrier->Action();
		m_charge = false;
		return;
	}
	// 押している間
	if (Input::IsDown(Input::Button::A, Input::Pad::P1)) {
		// フラグをfalseに
		m_parry = false;
		// アニメーションの再生速度を計算し一定カウントを越さないようにする
		float animSpeed = (kParryStopTime - m_animation.GetPlayCount()) / kParryStopTime;
		// アニメーションの再生速度を設定
		m_animation.SetAnimSpeed(animSpeed);
		m_MPGauge->Decrease(kParryMPDecrease);
		// アニメーションのカウントが一定以上いかないようにする(一応)
		if (m_animation.GetPlayCount() > kParryStopTime)
			m_animation.ResetPlayCount(kParryStopTime);
		m_charge = true;
	}
}

void Player::UpdateTransform(float deltaTime)
{
	// 入力量を取得
	float analogAmount = Input::PadAnalogAmount(Input::Joystick::Left, m_pad);
	// 入力角度を取得
	float analogAngle = Input::AnalogAngle(Input::Joystick::Left, m_pad);
	// 角度をラジアン角に変更
	analogAngle *= MyMath::ToRadian;
	// カメラの角度で回転するように
		analogAngle += CameraRotaY();

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
	m_move.Update(deltaTime);

	// トランスフォームを更新
	Transform transform = m_move.GetTransform();
	// 座標更新
	m_transform = transform;
	SetPosition(transform.position);
	/*printfDx("m_transform position\n");
	printfDx("x : %f / y : %f / z : %f\n", m_transform.position.x, m_transform.position.y, m_transform.position.z);*/
}

void Player::UpdateAnimation(float deltaTime)
{

	// アニメーションの更新
	m_animation.Update(deltaTime);
	// アニメーションのデバッグ表示
	//m_animation.Debug();
	// 割り込み再生またはアニメーション再生中なら処理しない
	if (m_animation.IsForcePlay() && m_animation.IsPlaying())return;
	// 次のアニメーションがどれか調べる
	Status::Player nextStatus;
	nextStatus = Status::Player::Neutral;
	// パリィ時またはボタンを押した瞬間
	if (m_status == Status::Player::Parry || (Input::IsPressed(Input::Button::A, m_pad))) {
		// パリィ状態に
		nextStatus = Status::Player::Parry;
	}
	// 移動の入力があるとき
	else if (Input::PadAnalogAmount(Input::Joystick::Left, m_pad)) {
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

void Player::ChangeAnimation(const Status::Player& status)
{
	// アニメーションの時間をリセット
	m_animation.ResetPlayCount();
	// アニメーションを再生
	m_animation.PlayAnimation(m_animData[static_cast<int>(status)]);
	// ステータスの更新
	m_status = status;
}

void Player::ResolveCollision(GameObject& other, const CollisionData& myData, const CollisionData& otherData, const Collision::Result& result)
{

	// 当たっていなければ即時return
	if (!result.isHit)return;

	// 衝突判定のフィルター
	// 高頻度で呼ばれるため無駄な判定は無視する
	if (myData.type == CollisionType::Sensor)return;
	// 足判定は接地専用で使われる
	bool isFoot = (myData.type == CollisionType::Foot);
	if (isFoot) {
		if (other.GetCollisionTag() == CollisionTag::Stage && result.normal.y > 0.0f) {
			m_isGroud = true;
		}
	}

	// 座標更新の計算処理


	// 押し戻し量を一時保存する
	Vector3 push = result.normal * result.penetration;
	switch (other.GetCollisionTag())
	{
	case CollisionTag::None:
		break;
	case CollisionTag::Enemy:
		if (myData.type == CollisionType::Body && otherData.type == CollisionType::Body) {
			m_move.AddPendingPush(push);
		}
		break;
	case CollisionTag::Stage:
	case CollisionTag::Wall: {
		Vector3 pushResult = m_transform.position + push;
		SetPosition(pushResult);
		break;
	}
	default:
		break;
	}

}

void Player::SetCameraAngle(const Vector3& position)
{
	Vector3 vec=position - m_transform.position;
	Vector3 rotate;
	rotate.z = 0;
	rotate.y = -atan2(vec.z, vec.x) - DX_PI_F * 0.5f;
	rotate.x = CameraRotaY();
	//printfDx("rotation.x : %d\n", static_cast<int>(rotate.x * MyMath::ToDegree));
	//printfDx("rotation.y : %d\n", static_cast<int>(rotate.y * MyMath::ToDegree));
	//printfDx("rotation.z : %d\n", static_cast<int>(rotate.z * MyMath::ToDegree));
	//m_pCamera->SetCameraAngle(rotate);
}

void Player::UpdateCollision()
{
	// 当たり判定の更新
	VECTOR hatRightFrame = MV1GetFramePosition(m_modelHandle, kHatRightFrameIndex);
	VECTOR HatLeftFrame = MV1GetFramePosition(m_modelHandle, kHatLeftFrameIndex);
	VECTOR headFrame = MV1GetFramePosition(m_modelHandle, kHeadFrameIndex);
	headFrame = VScale(VAdd(headFrame, VScale(VAdd(hatRightFrame, HatLeftFrame),0.5f)), 0.5f);
	VECTOR waistFrame = MV1GetFramePosition(m_modelHandle, kWaistFrameIndex);
	/*Vector3 hatCenter={(headPos1.x + headPos2.x)*0.5f,(headPos1.y + headPos2.y) * 0.5f,(headPos1.z + headPos2.z) * 0.5f };
	Vector3 get = { (hatCenter.x + headPos.x) * 0.5f,(hatCenter.y + headPos.y) * 0.5f ,(hatCenter.z + headPos.z) * 0.5f };*/
	m_capsule.SetMaxPosition({ headFrame.x, headFrame.y, headFrame.z });
	m_capsule.SetMinPosition({ waistFrame.x, waistFrame.y, waistFrame.z });

	for (auto& collision : m_collisions) {
		collision.shape->SetPosition(m_transform.position);
	}

	// カプセルのデバッグ表示
	//m_capsule.DebugDraw();
}

float Player::CameraRotaY()
{
	float yawRad = 0.0f;
	Vector3 forwaard = m_cameraView.GetForward();
	yawRad = atan2(forwaard.x,forwaard.z);

	return yawRad;
}

void Player::SetPosition(const Vector3& pos)
{
	m_transform.position = pos;
	m_move.SetTransform(m_transform);

	for (auto& collision : m_collisions) {
		collision.shape->SetPosition(m_transform.position);
	}
	// バリアの座標を設定
	if (m_pBarrier) {
		m_pBarrier->SetPosition(m_transform.position);
	}
}

Vector3 Player::GetCollisionCenterPos()
{
	return m_transform.position + kModelOffset;
}


void Player::SetBarrier(Barrier* barrier)
{
	m_pBarrier = barrier;
	// バリアのオフセットを設定
	m_pBarrier->SetOffset(kBarrierOffset);
}

