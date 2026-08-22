#include "Dragon.h"
#include"../Player/Player.h"
#include<string>
#include<math.h>
#include<cassert>
#include"../AnimationController.h"
#include"../CharacterMove.h"
#include"DragonAttack.h"
#include"DragonBreath.h"
#include"../../../Utility/Input.h"
#include"../../GameObjectManager.h"
#include"../CharacterManager.h"
#include"../../Map/RouteSearcher.h"
#include"../../Map/MapManager.h"
#include"../../../System/CollisionDataManager.h"
namespace {
	const char* const kModelDataName = "DragonModel";
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
	// 最大HP
	constexpr int kHPMax = 300;

	// 移動関連

	// 移動角度の補間割合
	constexpr float kLerpRad = 2.4f;
	// 移動速度
	constexpr float kMoveSpeed = 480;
	constexpr float kMaxSpeedRate = 4.0f;

	// モデルの大きさ倍率
	constexpr float kModelScale = 0.5f;

	// プレイヤー追従関連

	// プレイヤーの左右の追従座標の距離
	constexpr float kFollowOffset = 250;
	// 追いかける距離
	constexpr float kFollowLength = 450;
	// 追いかける距離の2乗
	constexpr float kFollowSqLength = kFollowLength * kFollowLength;
	// 追いかける距離(割り算時のキャッシュ)
	constexpr float kFollowLengthRatio = 1/kFollowLength;
	// 追いかける距離の2乗(割り算時のキャッシュ)
	constexpr float kFollowSqLengthRatio = kFollowLengthRatio* kFollowLengthRatio;

	// ターゲット追従関連

	// ターゲットを追従する距離
	constexpr float kTargetFollowLength = 500;
	// ターゲットを追従する距離の2乗
	constexpr float kTargetFollowSqLength = kTargetFollowLength * kTargetFollowLength;

	// 移動速度の減衰量
	constexpr float kAttenuationSpeed = 55;
	constexpr float kAttenuationMax = 0.9f;

	// 攻撃開始カウント
	constexpr float kAttackStartCount = 12.0f;
	// 攻撃終了カウント
	constexpr float kAttackEndCount = 22.0f;
	// 攻撃間隔
	constexpr float kAttackIntervalCount = 1.0f;

	constexpr int kCollisionID = 10;
}

Dragon::Dragon():
	m_animation(),
	m_animData(),
	m_status(Status::Dragon::Neutral),
	m_animHandle(),
	m_pTarget(nullptr),
	m_pMaster(nullptr),
	m_followState(FollowState::Normal),
	m_move(),
	m_attack(),
	m_attackFlag(false),
	m_canAttackFlag(false),
	m_speed(),
	m_breath(),
	m_pad(Input::Pad::Invalid)
{
	m_transform.Reset();

	for (int i = 0; i < static_cast<int>(Status::Dragon::Max);i++) {
		// インデックスを設定
		m_animData[i].index = i;
	}
	m_modelData = ResourceManager::GetInstance().GetModel(kModelDataName);
	Vector3 modelScale{ kModelScale ,kModelScale ,kModelScale };
	MV1SetScale(m_modelData->GetHandle(), modelScale.ToVECTOR());
	// アニメーション初期化
	m_animation.Init(m_modelData);

	m_move.SetTransform(m_transform);
	// 角度の補間速度を設定
	m_move.SetLerpSpeed(kLerpRad);
	// 移動速度を設定
	m_move.SetSpeed(kMoveSpeed);


	AddCollision(std::make_unique<Collision::Sphere>(Vector3::zero, 30), CollisionType::Body);
	// ブレスの初期化
	for (int i = 0; i < m_breath.size(); i++) {
		m_breath[i] = GameObjectManager::GetInstance().CreateObject<DragonBreath>();
	}
	CollisionParam param = CollisionDataManager::GetInstance().GetCollisionData(kCollisionID);
	AddCollision(std::make_unique<Collision::AABB>(param.position, param.size), CollisionType::Body);
	m_collisionTag = CollisionTag::Dragon;
}



Dragon::~Dragon()
{
	// ポインタの破棄
	if (m_pMaster) {
		m_pMaster = nullptr;
		delete m_pMaster;
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
	// アニメーション再生
	m_animation.PlayAnimation(m_animData[static_cast<int>(m_status)]);

}

void Dragon::Update(float deltaTime)
{
	// タイルIDの更新処理
	TileIDUpdate();
	// 入力による更新処理
	UpdateFromInput();

	// アニメーション速度を初期化
	m_animation.SetAnimSpeed();
	// ステータスによって分岐
	switch (m_status)
	{
	case Status::Dragon::Neutral:
	case Status::Dragon::Move:
		FollowUpdate(deltaTime);
		break;
	case Status::Dragon::Attack:
		AttackUpdate(deltaTime);
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
	Vector3 dd = m_transform.position;
	// アニメーション更新処理
	UpdateAnimation(deltaTime);
	// 移動
	m_move.Update(deltaTime);
	m_transform = m_move.GetTransform();
	// 攻撃アニメーション以外ではフラグをfalseに
	if (m_status != Status::Dragon::Attack)
		m_attackFlag = false;

	/*printfDx("x : %f / y : %f / z : %f\n", m_transform.position.x, m_transform.position.y, m_transform.position.z); 
	printfDx("m_speed : %f\n", m_speed);
	printfDx("followState : %d\n", m_followState);
	printfDx("dragon::CollisionType : %d\n", m_collisions[0].type);
	printfDx("dragon::TileID : %d\n", GetOnTileID());*/

}

void Dragon::TileIDUpdate()
{
	// 
	m_oldTileID = m_onTileID;
	m_onTileID = MapManager::GetInstance().GetIDFromWorldPos(m_transform.position);
	m_masterOldTileID = m_masterTileID;
	m_masterTileID = MapManager::GetInstance().GetIDFromWorldPos(m_pMaster->GetTransform().position);
	// 自身またはプレイヤーの所属しているマスが切り替わった時のみ以下の処理
	if (m_onTileID == m_oldTileID && m_masterTileID == m_masterOldTileID)return;
	// 自身とプレイヤー間の経路を生成
	CheckRouteManhattan();
	
}

void Dragon::UpdateFromInput()
{

	if (Input::IsPressed(Input::PadKey::RT, Input::Pad::P1)) {
		if (m_followState!=FollowState::Attack&&m_status!=Status::Dragon::Attack) {
			SetTarget(CharacterManager::GetInstance().CheckNearestCharacter(m_transform.position, Character::Type::Enemy));
			Call();
		}
		else {
			CallBack();
		}
	}
}

void Dragon::FollowUpdate(float deltaTime)
{
	// フォローの状態によって分岐
	switch (m_followState)
	{
	case FollowState::Normal:
		FollowPlayer();
		break;
	case FollowState::Attack:
		FollowTarget(deltaTime);
		break;
	case FollowState::RouteSearch:
		FollowRoute();
			break;
	default:
		break;
	}
}

void Dragon::AttackUpdate(float deltaTime)
{
	// 攻撃のインターバルをリセット
	m_attack.ResetCount();
	// アニメーションのカウントが一定を超えたら
	if (m_animation.GetPlayCount() > 6) {
		// アニメーション速度をゆっくりに
		m_animation.SetAnimSpeed(0.3f);
		for (int i = 0; i < kBleathCount; i++) {
			float time = kAttackStartCount + (i * kAttackIntervalCount);
			if (time > kAttackEndCount)break;
			if (!m_animation.CheckOverMoment(time))continue;
			Breath();

		}
		
	}
	// 角度の補間速度を設定
	m_move.SetLerpSpeed(kLerpRad);
	// 移動速度の減衰
	m_speed *= MyMath::Clamp(kAttenuationSpeed * deltaTime,0.0f,1.0f);
	// 移動速度を設定
	m_move.SetSpeed(m_speed);

}

void Dragon::ResolveCollision(GameObject& other, const CollisionData& myData, const CollisionData& otherData, const Collision::Result& result)
{
	Vector3 push = result.normal * result.penetration;

	switch (other.GetCollisionTag())
	{
	case CollisionTag::Wall: {
		Vector3 pushResult = m_transform.position + push;
		SetPosition(pushResult);
	
		break;
	}
	default:
		break;
	}
}


void Dragon::Call()
{
	if (!m_pTarget)return;

	m_followState = FollowState::Attack;
}

void Dragon::CallBack()
{
	m_followState = FollowState::Normal;
}

Vector3 Dragon::CheckFollowOffset()
{
	Transform targetTransform = m_pMaster->GetTransform();
	Vector3 OffsetLeft = Vector3::zero;
	Vector3 OffsetRight = Vector3::zero;
	Vector3 myPos = m_transform.position;
	Vector3  distance = myPos - targetTransform.position;
	OffsetLeft.x = -sinf(targetTransform.rotation.y - DX_PI_F * 0.5f);
	OffsetLeft.z = -cosf(targetTransform.rotation.y - DX_PI_F * 0.5f);
	OffsetLeft = OffsetLeft.Normalize();
	OffsetLeft *= kFollowOffset;
	OffsetRight = targetTransform.position - OffsetLeft;
	OffsetLeft += targetTransform.position;

	//DrawSphere3D(OffsetLeft.ToVECTOR(), 8, 10, 0xff0000, 0xff0000, FALSE);
	//DrawSphere3D(OffsetRight.ToVECTOR(), 8, 10, 0x0000ff, 0x0000ff, FALSE);


	float distanceRight = (myPos - OffsetRight).GetSqLength();
	float distanceLeft = (myPos - OffsetLeft).GetSqLength();
	float distancePlayer = (myPos - m_pMaster->GetTransform().position).GetSqLength();

	float resultDistance = distanceRight;
	Vector3  result= OffsetRight;
	if (resultDistance > distanceLeft) {
		resultDistance = distanceLeft;
		result = OffsetLeft;
	}
	if (resultDistance > distancePlayer) {
		resultDistance = distancePlayer;
		result = targetTransform.position;
	}

	return result;
}

void Dragon::SetPosition(const Vector3& pos)
{
	m_transform.position = pos;
	m_move.SetTransform(m_transform);

	for (auto& collision : m_collisions) {
		collision.shape->SetPosition(m_transform.position);
	}
}


void Dragon::FollowPlayer()
{
	assert(m_pMaster);

	Vector3 myPos = m_transform.position;
	Vector3  distance = myPos - CheckFollowOffset();
	float speed = distance.GetSqLength() * kFollowSqLengthRatio;
	if (speed > 3) {
		int i = 0;
	}

	m_speed = speed;
	m_speed = MyMath::Clamp(m_speed, 0.0f, kMaxSpeedRate);
		float angle = atan2(distance.x, distance.z);

		m_move.SetDesireRad(angle);
	if (distance.GetSqLength() > kFollowSqLength) {
		//m_speed = 1;
		float lerpSpeed = kLerpRad * MyMath::Clamp(m_speed,0.0f,1.0f);
		m_move.SetLerpSpeed(lerpSpeed);

	
	}
	else {
		float lerpSpeed = kLerpRad * MyMath::Clamp(m_speed, 0.0f, 1.0f);
		m_move.SetLerpSpeed(lerpSpeed);
	}

	m_move.SetSpeed(kMoveSpeed*m_speed);
	if (moveData.size() >= 5 && !IsTargetSameRoom()) {
		m_followState = FollowState::RouteSearch;

	}
}

void Dragon::FollowTarget(float deltaTime)
{
	Vector3 myPos = m_transform.position;
	Vector3  distance = myPos - m_pTarget->GetTransform().position;
	float angle = atan2(distance.x, distance.z);
	float speed = kAttenuationSpeed * deltaTime;
	m_speed *= MyMath::Clamp(speed,0.0f, kAttenuationMax);
	m_move.SetDesireRad(angle);
	if (distance.GetSqLength() > kTargetFollowSqLength) {
		m_speed = distance.GetSqLength() * kFollowSqLengthRatio;
		m_speed = MyMath::Clamp(m_speed, 0.0f, kMaxSpeedRate);
		float lerpSpeed = kLerpRad * MyMath::Clamp(m_speed,0.0f,1.0f);
		m_move.SetLerpSpeed(lerpSpeed);

		m_canAttackFlag = false;
		m_attack.ResetCount();

	}
	else {
		m_canAttackFlag = true;
		m_attack.Update(deltaTime);
		m_attackFlag = m_attack.GetAttackFlag();
	}

	m_speed = MyMath::Clamp(m_speed, 0.0f, 2.0f);
	m_move.SetSpeed(m_speed*kMoveSpeed);

}

void Dragon::FollowRoute()
{
	assert(m_pMaster);

	if (!moveData.size())return;
	Vector3 myPos = m_transform.position;
	Vector3  distance = myPos - MapManager::GetInstance().GetWorldPosFromID(moveData[0].m_sourceSquareID);
	Vector3  distancePlayer = myPos - m_pMaster->GetTransform().position;
	m_speed = distancePlayer.GetSqLength() * kFollowSqLengthRatio - 0.3f;
	m_speed = MyMath::Clamp(m_speed, 0.0f, kMaxSpeedRate);
	float angle = atan2(distance.x, distance.z);

	m_move.SetDesireRad(angle);
	if (distance.GetSqLength() > kFollowSqLength) {
		//m_speed = 1;
		float lerpSpeed = kLerpRad * MyMath::Clamp(m_speed, 0.0f, 1.0f);
		m_move.SetLerpSpeed(10);


	}
	else {
		float lerpSpeed = kLerpRad * MyMath::Clamp(m_speed, 0.0f, 1.0f);
		m_move.SetLerpSpeed(10);
	}

	m_move.SetSpeed(kMoveSpeed * m_speed);
	
	if (moveData.size() <= 5||IsTargetSameRoom()) {
		m_followState = FollowState::Normal;
	}


	if (m_onTileID == moveData[0].m_sourceSquareID) {
		moveData.erase(moveData.begin());
	}
}

void Dragon::UpdateAnimation(float deltaTime)
{
	// アニメーションの更新
	m_animation.Update(deltaTime);
	// アニメーションのデバッグ表示
	//m_animation.Debug();
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
	else if (m_speed>0.1f) {
		// 移動ステータスに
		//nextStatus = Status::Dragon::Move;
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
		}
		m_animation.ResetPlayCount();

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

void Dragon::Breath()
{
	// VECTOR型の座標を取得
	VECTOR headPos = MV1GetFramePosition(m_modelData->GetHandle(), 6), firePos = MV1GetFramePosition(m_modelData->GetHandle(), 11);
	// Vector3型に変換
	Vector3 head, fire;
	head = { headPos.x,headPos.y,headPos.z };
	fire = { firePos.x,firePos.y,firePos.z };
	// 座標の差を求める
	Vector3 differ = fire - head;
	for (int i = 0; i < m_breath.size(); i++) {
		// 生成済みならスキップ
		if (m_breath[i]->IsActive())continue;
		// ブレスを1つ生成
		m_breath[i]->Setup(fire, differ);
		break;
	}
}

bool Dragon::IsTargetSameRoom()
{
	int myRoomID = MapManager::GetInstance().GetRoomID(m_onTileID);
	int masterRoomID = MapManager::GetInstance().GetRoomID(m_pMaster->GetOnTileID());
	//printfDx("myRoomID : %d\n", myRoomID);
	//printfDx("masterRoomID : %d\n", masterRoomID);
	if (myRoomID == -1 || masterRoomID == -1)return false;
	if (myRoomID == masterRoomID)return true;
	return false;
}

void Dragon::CheckRouteManhattan()
{
	// 自身とプレイヤーのマスを取得
	m_routeSearchTileID = GetOnTileID();
	m_routeSearchPlayerTileID = m_pMaster->GetOnTileID();
	// 自身のマスが経路探索での通行不可マスの時
	if (!CanMoveManhattan(MapManager::GetInstance().GetTile(GetOnTileID())->GetSquareData())) {
		// 周囲8マスのうち最も近い通行可能マスを取得
		m_routeSearchTileID = GetNearestCanMoveTile(m_transform.position);
	}
	// プレイヤーのマスが経路探索での通行不可マスの時
	if (!CanMoveManhattan(MapManager::GetInstance().GetTile(m_pMaster->GetOnTileID())->GetSquareData())) {
		// 周囲8マスのうち最も近い通行可能マスを取得
		m_routeSearchPlayerTileID = GetNearestCanMoveTile(m_pMaster->GetTransform().position);
	}
	// 自身とプレイヤーが同じマスの場合は経路を生成しない
	if (m_routeSearchTileID == m_routeSearchPlayerTileID)return;

	// 通行可否を調べる関数ポインタ
	std::function<bool(SquareData*)>tilecheck;
	tilecheck = [&](SquareData* data) {
		return CanMoveManhattan(data);
		};
	// 経路を生成
	std::vector<ManhattanMoveData>route = RouteSearcher::GetInstance().RouteSearchManhattan(m_routeSearchTileID, m_routeSearchPlayerTileID, tilecheck);
	moveData.clear();
	// 経路のコストをキャッシュ
	int routeSize = route.size();
	for (int i = 0; i < routeSize; i++) {
		// 経路の後ろから順に追加
		moveData.push_back(route[route.size()-1]);
		// 追加した要素を削除
		route.erase(route.end() - 1);
	}
	// 経路生成出来たかどうかチェック
	if (!moveData.size())return;
	// 最初のマス(自身のマス)を削除
	moveData.erase(moveData.begin());
}

bool Dragon::CanMoveManhattan(SquareData* square)
{
	// nullptrなら処理しない
	if (!square)return false;
	// タイルの種類を調べる
	MapConst::eTerrain terrain = square->GetTerrain();
	// タイルが不正値なら通行不可
	if (terrain == MapConst::eTerrain::Invalid)return false;
	// 壁以外なら通行可能
	return terrain!=MapConst::eTerrain::Wall;
}

int Dragon::GetNearestCanMoveTile(const Vector3& position)
{
	// 指定した座標の所属するマスIDを取得
	int baseID = MapManager::GetInstance().GetIDFromWorldPos(position);
	// 取得したIDから基準となるマスの取得
	MapTile* square = MapManager::GetInstance().GetTile(baseID);
	// 最短距離を格納する変数
	float minLength = -1;
	// 最短距離マスのIDを格納する変数
	int resultID = -1;
	// 基準のマスが通行可能なら基準マスを返す
	if (CanMoveManhattan(square->GetSquareData()))return baseID;
	// 8方向を調べる
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionEight::Max); i++) {
		// 方向を取得
		MapConst::eDirectionEight direction = static_cast<MapConst::eDirectionEight>(i);
		// 取得した方向からマスを取得
		square=MapManager::GetInstance().GetToDirSquare(baseID, direction);
		// nullptrならスルー
		if (!square)continue;
		// 通行不可ならスルー
		if (!CanMoveManhattan(square->GetSquareData()))continue;
		// 指定方向のマスとの距離を求める
		float distance = (position - MapManager::GetInstance().GetWorldPosFromID(square->GetId())).GetSqLength();
		// minLengthに正常な値が入っていて、かつ最短距離でなければスルー
		if (minLength > 0 && minLength < distance)continue;
		// 最短距離なら
		// 最短距離の更新
		minLength = distance;
		// 最短距離マスのIDを更新
		resultID = square->GetId();
	}

	return resultID;
}

