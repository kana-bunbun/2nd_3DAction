#include "HealBottle.h"
#include "../../../System/ResourceManager.h"
#include"../../../Utility/MyRandom.h"
namespace {
	const char* const kModelPath = "bottlePotionHealth";

	// 投げる力の強さ
	constexpr float kThrowPower=1200.0f;
	// 落下速度
	constexpr float kFallSpeed = kThrowPower *2.5f;

	// 描画の中心となるフレームの位置
	constexpr int kDrawCenterFrameNum = 1;
	// 効果発動の最大カウント
	constexpr float kEffectMaxCount = 3.0f;
	// 透明度の最大値
	constexpr float kAlphaMax = 0.5f;
	// 効果の範囲
	constexpr float kEffectRadius = 420;
	// 回復処理発動インターバル
	constexpr float kEffectInterval = 0.3f;
	constexpr float kBodyCollisionAxis = 30;

}

HealBottle::HealBottle() :
	m_alpha(0),
	m_isTrans(false)
{
	m_rotateSpeed = Vector3::zero;
	m_modelData = ResourceManager::GetInstance().GetModel(kModelPath);
	AddCollision(std::make_unique<Collision::Sphere>(m_transform.position, kEffectRadius), CollisionType::Null);
	Vector3 collisionSize = { kBodyCollisionAxis,kBodyCollisionAxis ,kBodyCollisionAxis };
	AddCollision(std::make_unique<Collision::AABB>(m_transform.position, collisionSize), CollisionType::Invalid);
}

HealBottle::~HealBottle()
{
	
}

void HealBottle::Init()
{

}

void HealBottle::End()
{

}

void HealBottle::Setup(const Transform& transform)
{
	m_isActive = true;
	m_transform.position = transform.position;
	
	// 回転速度をランダムに求める
	RandomRotate();
	m_transform.rotation = m_rotateSpeed;
	m_moveVector.y = kThrowPower;

	m_isEffect = false;
	m_effectCount = kEffectMaxCount;

	m_isTrans = false;
	m_collisions[0].type = CollisionType::Null;

}

void HealBottle::Update(float deltaTime)
{
	// 効果発動前の処理
	BeforeEffectUpdate(deltaTime);
	// 地面に落下した時
	if (m_transform.position.y < 0&&m_moveVector.y<0) {
		// 効果のセットアップ
		EffectSetup();
	}

	// 効果発動中でなければ即時return
	if (!m_isEffect)return;
	// 効果の更新処理
	EffectUpdate(deltaTime);
}

void HealBottle::Draw()
{
	printfDx("healBottle::CollisionType : %d\n", m_collisions[0].type);
	printfDx("healBottle::TileID : %d\n", GetOnTileID());
	if (m_isEffect) {
		DrawEffect();
	}
	else {
		DrawModel();
	}
}

void HealBottle::DrawModel()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelData->GetHandle() == -1)return;

	MV1SetRotationXYZ(m_modelData->GetHandle(), m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelData->GetHandle(), m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelData->GetHandle());
}

void HealBottle::DrawEffect()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_alpha);
	DrawSphere3D(m_transform.position.ToVECTOR(), kEffectRadius, 10, Color::kGreen, Color::kGreen, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

}

void HealBottle::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{
	Vector3 push = result.normal * result.penetration;
	switch (other.GetCollisionTag())
	{
	case CollisionTag::Wall:
		// エフェクトの当たり判定なら処理を抜ける
		if (myData.type == CollisionType::Heal)break;
		SetPosition(m_transform.position + push);
		EffectSetup();
		break;
	case CollisionTag::Player:
	case CollisionTag::Dragon:
	case CollisionTag::Enemy:
		if (myData.type == CollisionType::Invalid)break;
		if (m_activationCount)break;
	// 一旦適当な値の回復処理を呼んでおく
	other.Heal(2);
		break;
	default:
		break;
	}

}

void HealBottle::EffectSetup()
{
	// 落下速度を0に
	m_moveVector.y = 0;
	// Y座標をクランプ
	m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
	// エフェクトフラグを更新
	m_isEffect = true;
}

void HealBottle::BeforeEffectUpdate(float deltaTime)
{
	// 効果発動中なら処理しない
	if (m_isEffect)return;
	// 回転させる
	m_transform.rotation += m_rotateSpeed * deltaTime;
	// 落下速度を更新
	m_moveVector.y -= kFallSpeed * deltaTime;
	// 落下させる
	m_transform.position.y += m_moveVector.y * deltaTime;
	// 効果発動前は衝突判定をチェックしない
	m_collisions[0].type = CollisionType::Null;
}

void HealBottle::EffectUpdate(float deltaTime)
{
	// 効果発動中は衝突判定をチェックする
	m_collisions[0].type = CollisionType::Heal;
	// カウントダウン
	m_effectCount -= deltaTime;
	// カウントに応じて透明度を求める
	m_alpha = m_effectCount / kEffectMaxCount;
	// 透明度をクランプ
	m_alpha = MyMath::Clamp(m_alpha, 0.0f, kAlphaMax);
	// 透明度フラグの更新
	m_isTrans = true;
	// 効果発動のカウントを更新
	m_activationCount += deltaTime;
	// 効果カウントがインターバルを超えたら
	if (m_activationCount > kEffectInterval) {
		m_activationCount = 0;
	}
	
	// カウントが0になったら
	if (m_effectCount <= 0) {
		// カウントを0に
		m_effectCount = 0;
		// 効果発動フラグを更新
		m_isEffect = false;
		// 非アクティブにする
		m_isActive = false;
	}
}
