#include "MolotovCocktail.h"
#include "ItemManager.h"
#include "../../../System/ResourceManager.h"
#include"../../GameObjectParam.h"
namespace {
	const char* const kModelPath = "molotovCocktail";

	constexpr float kThrowRadian = 75 * MyMath::ToRadian;
	constexpr float kMoveSpeed = 1500.0f;
	constexpr float kThrowMaxRadian = 180 * MyMath::ToRadian;
	constexpr float kEffectMaxCount = 3.0f;
	constexpr float kAlphaMax = 0.5f;
	constexpr float kEffectRadius = 300;
	constexpr float kBodyCollisionRadius = 30;
	constexpr float kBodyCollisionAxis = 30;
	// 攻撃のインターバル
	constexpr float kAttackInterval = 0.5f;

}
MolotovCocktail::MolotovCocktail()
{
	m_modelData = ResourceManager::GetInstance().GetModel(kModelPath);
	AddCollision(std::make_unique<Collision::Sphere>(m_transform.position, kEffectRadius),CollisionType::Null);
	AddCollision(std::make_unique<Collision::Sphere>(m_transform.position, kBodyCollisionRadius),CollisionType::Attack);
	Vector3 collisionSize = { kBodyCollisionAxis,kBodyCollisionAxis ,kBodyCollisionAxis };
	AddCollision(std::make_unique<Collision::AABB>(m_transform.position, collisionSize),CollisionType::Invalid);
}

MolotovCocktail::~MolotovCocktail()
{

}

void MolotovCocktail::Init()
{

}

void MolotovCocktail::Update(float deltaTime)
{
	BeforeEffectUpdate(deltaTime);
	if (m_transform.position.y < 0) {

	EffectSetup();
	}
	if (!m_isEffect)return;
	EffectUpdate(deltaTime);
}

void MolotovCocktail::End()
{

}

void MolotovCocktail::Draw()
{
	printfDx("molotov::CollisionType : %d\n", m_collisions[0].type);
	printfDx("molotov::TileID : %d\n", GetOnTileID());
	if (m_isEffect) {
		DrawEffect();
	}
	else {
		DrawModel();
	}
}
void MolotovCocktail::DrawModel()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelData->GetHandle() == -1)return;

	MV1SetRotationXYZ(m_modelData->GetHandle(), m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelData->GetHandle(), m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelData->GetHandle());
}

void MolotovCocktail::DrawEffect()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_alpha);
	DrawSphere3D(m_transform.position.ToVECTOR(), kEffectRadius, 10, Color::kRed, Color::kRed, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

}
void MolotovCocktail::ResolveCollision(GameObject& other, const CollisionData& myData, const CollisionData& otherData, const Collision::Result& result)
{
	Vector3 push = result.normal * result.penetration;
	switch (other.GetCollisionTag())
	{
	case CollisionTag::Wall:
		// エフェクトの当たり判定なら処理を抜ける
		if (myData.type == CollisionType::Attack)break;
		SetPosition(m_transform.position + push);
		EffectSetup();
		break;
	case CollisionTag::Player:
	case CollisionTag::Dragon:
	case CollisionTag::Enemy:
		// エフェクトの当たり判定でなければ処理を抜ける
		if (myData.type == CollisionType::Invalid)break;
		if (m_activationCount)break;
		other.Damage(1);
		break;
	default:
		break;
	}
}

void MolotovCocktail::Setup(const Transform & transform)
{
	Camera::CameraView view = ItemManager::GetInstance().GetCameraView();
	Vector3 move=(view.target - view.position).Normalize();
	Vector3 offset = Vector3::zero;
	offset.y = sinf(kThrowRadian);
	move += offset.Normalize();
	m_activationCount = 0;
	if (move.GetSqLength()) {
		m_moveVector = move.Normalize();
		m_moveVector.x = -sinf(transform.rotation.y);
		m_moveVector.z = -cosf(transform.rotation.y);
		m_moveVector.y = MyMath::Clamp(m_moveVector.y, 0.0f, kThrowMaxRadian);
	}

	m_transform.position = transform.position;

	RandomRotate();
	m_transform.rotation = m_rotateSpeed;
	m_effectCount = kEffectMaxCount;
	m_isActive = true;
	m_isEffect = false;
}

void MolotovCocktail::EffectSetup()
{
	m_isEffect = true;
	m_moveVector = Vector3::zero;
}

void MolotovCocktail::BeforeEffectUpdate(float deltaTime)
{
	// 移動方向をキャッシュ
	Vector3 moveValue = m_moveVector * deltaTime * kMoveSpeed;
	// 座標の更新
	m_transform.position += moveValue;
	// Y軸方向(落下速度)を更新
	m_moveVector.y -= deltaTime;
	// 回転させる
	m_transform.rotation += m_rotateSpeed * deltaTime;
}

void MolotovCocktail::EffectUpdate(float deltaTime)
{
// カウントダウン
	m_effectCount -= deltaTime;
	// カウントに応じて透明度を求める
	m_alpha = m_effectCount / kEffectMaxCount;
	// 透明度をクランプ
	m_alpha = MyMath::Clamp(m_alpha, 0.0f, kAlphaMax);
	// 攻撃の当たり判定チェックを開始
	m_collisions[0].type = CollisionType::Attack;
	// 攻撃カウントを加算
	m_activationCount += deltaTime;
	if (m_activationCount > kAttackInterval) {
		m_activationCount = 0;
	}
	// カウントが0になったら
	if (m_effectCount < 0) {
		// カウントを0に
		m_effectCount = 0;
		// 効果発動フラグの更新
		m_isEffect = false;
		// 非アクティブ状態にする
		m_isActive = false;
	}


}
