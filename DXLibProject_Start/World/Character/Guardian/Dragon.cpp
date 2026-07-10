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

namespace {
	const char* const kFilePath="Resource\\Dragon\\ChaDragon\\";
	const char* const kModelPath = "Model.mv1";
	const char* const kMotionPath = "Motions\\";
	const char* const kAnimPath[static_cast<int>(Status::Dragon::Max)] = {
		 "Move.mv1",
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
	constexpr float kLerpRad = 2.4f;
	// 移動速度
	constexpr float kMoveSpeed = 480;
	constexpr float kMaxSpeedRate = 4.0f;

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

	// 移動速度の減衰量
	constexpr float kAttenuationSpeed = 55;
	constexpr float kAttenuationMax = 0.9f;

	// 攻撃開始カウント
	constexpr float kAttackStartCount = 12.0f;
	// 攻撃終了カウント
	constexpr float kAttackEndCount = 22.0f;
	// 攻撃間隔
	constexpr float kAttackIntervalCount = 1.0f;

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

	std::string path = kFilePath;
	// モデルの読み込み
	m_modelHandle = MV1LoadModel((path+kModelPath).c_str());
	MV1SetScale(m_modelHandle, Vector3(kModelScale, kModelScale, kModelScale).ToVECTOR());
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
		m_animation.AddAnim(m_animHandle[i]);
		// インデックスを設定
		m_animData[i].index = i;
	}
	// アニメーション初期化
	m_animation.Init(m_modelHandle);
	// 座標を設定
	m_transform.position+=kPosOffset;

	m_move.SetTransform(m_transform);
	// 角度の補間速度を設定
	m_move.SetLerpSpeed(kLerpRad);
	// 移動速度を設定
	m_move.SetSpeed(kMoveSpeed);

	m_HPGauge = std::make_unique<Gauge>();

	AddCollision(std::make_unique<Collision::Sphere>(Vector3::zero, 0), GameObject::CollisionType::Body);
	// ブレスの初期化
	for (int i = 0; i < m_breath.size(); i++) {
		m_breath[i] = GameObjectManager::GetInstance().CreateObject<DragonBreath>();
	}
	float sizeAxis = 300;
	Vector3 size = { sizeAxis,sizeAxis,sizeAxis };
	AddCollision(std::make_unique<Collision::AABB>(m_transform.position, size), GameObject::CollisionType::Body);
	m_collisionTag = GameObject::CollisionTag::Dragon;
}



Dragon::~Dragon()
{
	// モデルハンドルを破棄
	MV1DeleteModel(m_modelHandle);
	// アニメーションハンドルを破棄
	for (int& anim : m_animHandle)
		MV1DeleteModel(anim);
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
	m_oldTileID = m_onTileID;
	m_onTileID = MapManager::GetInstance().GetIDFromWorldPos(m_transform.position);
	m_masterOldTileID = m_masterTileID;
	m_masterTileID= MapManager::GetInstance().GetIDFromWorldPos(m_pMaster->GetTransform().position);
	if(m_onTileID!=m_oldTileID||m_masterTileID!=m_masterOldTileID)
	CheckRouteManhattan();
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
	// アニメーション更新処理
	UpdateAnimation(deltaTime);
	// 移動
	m_move.Update(deltaTime);
	m_transform = m_move.GetTransform();
	// 攻撃アニメーション以外ではフラグをfalseに
	if (m_status != Status::Dragon::Attack)
		m_attackFlag = false;

	m_HPGauge->Clamp();
	printfDx("x : %f / y : %f / z : %f\n", m_transform.position.x, m_transform.position.y, m_transform.position.z); 
	printfDx("m_speed : %f\n", m_speed);
	printfDx("followState : %d\n", m_followState);

	Vector3 myTile = MapManager::GetInstance().GetWorldPosFromID(m_routeSearchTileID);
	Vector3 masterTile = MapManager::GetInstance().GetWorldPosFromID(m_routeSearchPlayerTileID);
	Vector3 Tile = MapManager::GetInstance().GetWorldPosFromID(m_onTileID);
	DrawSphere3D(myTile.ToVECTOR(), 200, 20, Color::kCyan, Color::kCyan, TRUE);
	DrawSphere3D(masterTile.ToVECTOR(), 200, 20, Color::kMagenta, Color::kMagenta, TRUE);
	DrawSphere3D(Tile.ToVECTOR(), 20, 20, Color::kRed, Color::kRed, TRUE);
	//DrawSphere3D(m_transform.position.ToVECTOR(), 500, 10, 0xff0000, 0xff0000, TRUE);
}

void Dragon::UpdateFromInput()
{

	if (Input::IsPressed(Input::Button::RT, Input::Pad::P1)) {
		if (Input::IsDown(Input::Button::LT, Input::Pad::P1)) {
			SetTarget(CharacterManager::GetInstance().CheckNearestCharacter(m_transform.position, Character::Type::Enemy));
			Call();
		}
		else
			CallBack();
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
		if (push.GetSqLength() > 900) {
			int s = 0;
		}
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
	Vector3 myPos = m_transform.position-kPosOffset;
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
	myPos -= kPosOffset;
	Vector3  distance = myPos - CheckFollowOffset();
	float speed = distance.GetSqLength() * kFollowSqLengthRate;
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
	Vector3 myPos = m_transform.position- kPosOffset;
	Vector3  distance = myPos - m_pTarget->GetTransform().position;
	float angle = atan2(distance.x, distance.z);
	float speed = kAttenuationSpeed * deltaTime;
	m_speed *= MyMath::Clamp(speed,0.0f, kAttenuationMax);
	m_move.SetDesireRad(angle);
	if (distance.GetSqLength() > kTargetFollowSqLength) {
		m_speed = distance.GetSqLength() * kFollowSqLengthRate;
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
	myPos -= kPosOffset;
	Vector3  distance = myPos - MapManager::GetInstance().GetWorldPosFromID(moveData[0].m_sourceSquareID);
	Vector3  distancePlayer = myPos - m_pMaster->GetTransform().position;
	m_speed = distancePlayer.GetSqLength() * kFollowSqLengthRate - 0.3f;
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
	VECTOR headPos = MV1GetFramePosition(m_modelHandle, 6), firePos = MV1GetFramePosition(m_modelHandle, 11);
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
	printfDx("myRoomID : %d\n", myRoomID);
	printfDx("masterRoomID : %d\n", masterRoomID);
	if (myRoomID == -1 || masterRoomID == -1)return false;
	if (myRoomID == masterRoomID)return true;
	return false;
}

void Dragon::CheckRouteManhattan()
{
	m_routeSearchTileID = GetOnTileID();
	m_routeSearchPlayerTileID = m_pMaster->GetOnTileID();
	if (!CanMoveManhattan(MapManager::GetInstance().GetTile(GetOnTileID())->GetSquareData())) {
		m_routeSearchTileID = GetNearestCanMoveTile(m_transform.position);

	}
	if (!CanMoveManhattan(MapManager::GetInstance().GetTile(m_pMaster->GetOnTileID())->GetSquareData())) {
		m_routeSearchPlayerTileID = GetNearestCanMoveTile(m_pMaster->GetTransform().position);

	}
	/*if (!CanMoveManhattan(MapManager::GetInstance().GetTile(GetOnTileID())->GetSquareData()))
	{
		return;
	}
	if (!CanMoveManhattan(MapManager::GetInstance().GetTile(m_pMaster->GetOnTileID())->GetSquareData()))
	{
		return;
	}*/
	if (m_routeSearchTileID == m_routeSearchPlayerTileID)
	{
		return;
	}
	std::function<bool(SquareData*)>tilecheck;
	tilecheck = [&](SquareData* data) {
		return CanMoveManhattan(data);
		};
	std::vector<ManhattanMoveData>route = RouteSearcher::GetInstance().RouteSearchManhattan(m_routeSearchTileID, m_routeSearchPlayerTileID, tilecheck);
	moveData.clear();
	int routeSize = route.size();
	for (int i = 0; i < routeSize; i++) {
		moveData.push_back(route[route.size()-1]);
		route.erase(route.end() - 1);
	}
	if(moveData.size())
	moveData.erase(moveData.begin());
}

bool Dragon::CanMoveManhattan(SquareData* square)
{
	if (!square)return false;
	MapConst::eTerrain terrain = square->GetTerrain();
	if (terrain == MapConst::eTerrain::Invalid)return false;
	return terrain!=MapConst::eTerrain::Wall;
}

int Dragon::GetNearestCanMoveTile(const Vector3& position)
{
	int baseID = MapManager::GetInstance().GetIDFromWorldPos(position);
	MapTile* square = MapManager::GetInstance().GetTile(baseID);
	float minDistance = -1;
	int resultID = -1;
	if (CanMoveManhattan(square->GetSquareData()))return baseID;
	for (int i = 0; i < static_cast<int>(MapConst::eDirectionEight::Max); i++) {
		MapConst::eDirectionEight direction = static_cast<MapConst::eDirectionEight>(i);
		square=MapManager::GetInstance().GetToDirSquare(baseID, direction);
		if (!square)continue;
		if (!CanMoveManhattan(square->GetSquareData()))continue;
		float distance = (position - MapManager::GetInstance().GetWorldPosFromID(square->GetId())).GetSqLength();
		if (minDistance > 0 && minDistance < distance)continue;
		minDistance = distance;
		resultID = square->GetId();
	}
	return resultID;
}

