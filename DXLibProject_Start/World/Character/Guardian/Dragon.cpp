#include "Dragon.h"
#include"../Player/Player.h"
#include<string>
#include<math.h>
#include<cassert>
#include"../AnimatioController.h"
#include"../CharacterMove.h"
#include"DragonAttack.h"
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
		false,
		false,
		false,
	};
	constexpr bool kForcePlay[static_cast<int>(Status::Dragon::Max)]{
		false,
		false,
		true,
		true,
		true,
	};

	// 移動関連

	// 移動角度の補間割合
	constexpr float kLerpRad = 0.04f;
	// 移動速度
	constexpr float kMoveSpeed = 8 ;

	// モデルの大きさ倍率
	constexpr float kModelScale = 0.5f;
	// 座標のオフセット
	constexpr Vector3 kPosOffset = { 0.0f,70.0f,0.0f };

	// プレイヤー追従関連

	// プレイヤーの左右の追従座標の距離
	constexpr float kFollowOffset = 250;
	// 追いかける距離
	constexpr float kFollowLength = 450;
	// 追いかける距離の2乗
	constexpr float kFollowSqLength = kFollowLength * kFollowLength;
	// 追いかける距離(割り算時のキャッシュ)
	constexpr float kFollowLengthRate = 1/kFollowLength;
	// 追いかける距離の2乗(割り算時のキャッシュ)
	constexpr float kFollowSqLengthRate = kFollowLengthRate* kFollowLengthRate;

	// ターゲット追従関連

	// ターゲットを追従する距離
	constexpr float kTargetFollowLength = 500;
	// ターゲットを追従する距離の2乗
	constexpr float kTargetFollowSqLength = kTargetFollowLength * kTargetFollowLength;

}
Dragon::Dragon() :
	m_animation(),
	m_animData(),
	m_status(Status::Dragon::Neutral),
	m_animHandle(),
	m_pTarget(nullptr),
	m_pPlayer(nullptr),
	m_followState(FollowState::Normal),
	m_move(),
	m_attack(),
	m_attackFlag(false),
	m_canAttackFlag(false),
	m_speed()
{
	m_transform.Reset();

	std::string path = kFilePath;
	m_modelHandle = MV1LoadModel((path+kModelPath).c_str());
	MV1SetScale(m_modelHandle, Vector3(kModelScale, kModelScale, kModelScale).ToVECTOR());
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

	m_transform.position+=kPosOffset;
	m_move.SetTransform(m_transform);
	m_move.SetLerpSpeed(kLerpRad);
	m_move.SetSpeed(kMoveSpeed);
}

Dragon::~Dragon()
{
	MV1DeleteModel(m_modelHandle);
	if (m_pPlayer) {
		m_pPlayer = nullptr;
		delete m_pPlayer;
	}
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

	m_status = Status::Dragon::Neutral;
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);

}

void Dragon::Update()
{
	//m_animation.Update();

	//printfDx("デバッグ\n");
	//m_animation.Debug();
	m_animation.SetAnimSpeed();
	switch (m_status)
	{
	case Status::Dragon::Neutral:
	case Status::Dragon::Move:
		FollowUpdate();
		break;
	case Status::Dragon::Attack:
		AttackUpdate();
		break;
	case Status::Dragon::Damage:
		break;
	case Status::Dragon::Dead:
		break;
	case Status::Dragon::Max:
		break;
	default:
		break;
	}
	UpdateAnimation();
	if (m_status != Status::Dragon::Attack)
		m_attackFlag = false;
}

void Dragon::FollowUpdate()
{
	// フォローの状態によって分岐
	switch (m_followState)
	{
	case FollowState::Normal:
		FollowPlayer();
		break;
	case FollowState::Attack:
		FollowTarget();
		break;
	default:
		break;
	}
}

void Dragon::AttackUpdate()
{
	m_attack.ResetCount();
	if(m_animation.GetPlayCount()>6)
	m_animation.SetAnimSpeed(0.3f);
	m_move.SetLerpSpeed(kLerpRad);
	m_speed *= 0.96f;
	m_move.SetSpeed(m_speed);
	m_move.Update();
	m_transform = m_move.GetTransform();
	printfDx("Attack\n");
	printfDx("canAttack : %d\n",m_canAttackFlag);
}

void Dragon::ResolveCollision(GameObject & other, const Collision::Result & result)
{

}

void Dragon::Call(GameObject* target)
{

	m_followState = FollowState::Attack;
	m_pTarget = target;
}

void Dragon::CallBack()
{
	m_followState = FollowState::Normal;
}

Vector3 Dragon::CheckFollowOffset()
{
	Transform targetTransform = m_pPlayer->GetTransform();
	Vector3 OffsetLeft = Vector3::zero;
	Vector3 OffsetRight = Vector3::zero;
	Vector3 myPos = m_transform.position-kPosOffset;
	Vector3  distance = myPos - targetTransform.position;
	OffsetLeft.x = -sinf(targetTransform.rotation.y - DX_PI_F * 0.5f);
	OffsetLeft.z = -cosf(targetTransform.rotation.y - DX_PI_F * 0.5f);
	OffsetLeft = OffsetLeft.Normalize();
	OffsetLeft *= kFollowOffset;
	OffsetRight = targetTransform.position - OffsetLeft;
	OffsetLeft += targetTransform.position;
	DrawSphere3D(OffsetLeft.ToVECTOR(), 80, 10, 0xff0000, 0xff0000, FALSE);
	DrawSphere3D(OffsetRight.ToVECTOR(), 80, 10, 0x0000ff, 0x0000ff, FALSE);


	float distanceRight = (myPos - OffsetRight).GetSqLength();
	float distanceLeft = (myPos - OffsetLeft).GetSqLength();
	return (distanceLeft > distanceRight) ? OffsetRight : OffsetLeft;
}

void Dragon::FollowPlayer()
{
	assert(m_pPlayer);
	Vector3 myPos = m_transform.position;
	myPos -= kPosOffset;
	Vector3  distance = myPos - CheckFollowOffset();
	m_speed = distance.GetSqLength()*kFollowSqLengthRate;
	m_speed = MyMath::Clamp(m_speed, 0.0f, 3.0f);
		float angle = atan2(distance.x, distance.z);

		printfDx("dddddddddd : %f\n", angle * MyMath::ToDegree);
		m_move.SetDesireRad(angle);
	if (distance.GetSqLength() > kFollowSqLength) {
		//m_speed = 1;
		float lerpSpeed = kLerpRad * m_speed;
		m_move.SetLerpSpeed(lerpSpeed);
		m_status = Status::Dragon::Move;

	
	}
	else {
	}

		printfDx("m_speed: %f\n", m_speed);
	m_move.SetSpeed(kMoveSpeed*m_speed);
	m_move.Update();
	m_transform = m_move.GetTransform();
}

void Dragon::FollowTarget()
{
	Vector3 myPos = m_transform.position- kPosOffset;
	Vector3  distance = myPos - m_pTarget->GetTransform().position;
	float angle = atan2(distance.x, distance.z);

	m_speed *= 0.96f;
	printfDx("dddddddddd : %f\n", angle * MyMath::ToDegree);
	m_move.SetDesireRad(angle);
	if (distance.GetSqLength() > kTargetFollowSqLength) {
		m_speed = distance.GetSqLength() * kFollowSqLengthRate;

		float lerpSpeed = kLerpRad * m_speed;
		m_move.SetLerpSpeed(lerpSpeed);

		m_canAttackFlag = false;
		m_attack.ResetCount();

	}
	else {
		m_canAttackFlag = true;
		m_attack.Update();
		m_attackFlag = m_attack.GetAttackFlag();
	}

	printfDx("m_attack: %d\n", m_attack.GetAttackFlag());
	printfDx("m_attackCount: %d\n", m_attack.GetCount());
	printfDx("m_speed: %f\n", m_speed);
	m_speed = MyMath::Clamp(m_speed, 0.0f, 1.0f);
	m_move.SetSpeed(m_speed*kMoveSpeed);
	m_move.Update();
	m_transform = m_move.GetTransform();
}

void Dragon::UpdateAnimation()
{
	// アニメーションの更新
	m_animation.Update();
	// アニメーションのデバッグ表示
	m_animation.Debug();
	// 割り込み再生またはアニメーション再生中なら処理しない
	if (m_animation.IsForcePlay() && m_animation.IsPlaying())return;
	// 次のアニメーションがどれか調べる
	Status::Dragon nextStatus;
	nextStatus = Status::Dragon::Neutral;
	// パリィ時またはボタンを押した瞬間
	if (m_attackFlag) {
		// パリィ状態に
		nextStatus = Status::Dragon::Attack;
	}
	// 移動の入力があるとき
	else if (m_speed>0.1f) {
		// 移動ステータスに
		nextStatus = Status::Dragon::Move;
	}
	// アニメーションが終了していればアイドル状態に
	if (!m_animation.IsPlaying()) {
		nextStatus = Status::Dragon::Neutral;
		//m_followState = FollowState::Normal;
	}

	// ステータスが異なっていたらアニメーションの変更
	if (m_status != nextStatus) {

		// NeutralからMoveまたはMoveからNeutralの時はアニメーションの時間をリセットしない
		if ((m_status != Status::Dragon::Neutral && nextStatus != Status::Dragon::Move) ||
			(nextStatus != Status::Dragon::Neutral && m_status != Status::Dragon::Move)) {
		// アニメーションの時間をリセット
		m_animation.ResetPlayCount();
		}

		ChangeAnimation(nextStatus);
	}

}

void Dragon::ChangeAnimation(const Status::Dragon & status)
{
	
	// アニメーションを再生
	m_animation.PlayAnimation(m_animData[static_cast<int>(status)]);
	// ステータスの更新
	m_status = status;
}

