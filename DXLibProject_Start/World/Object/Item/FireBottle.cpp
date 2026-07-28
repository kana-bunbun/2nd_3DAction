#include "FireBottle.h"
#include "ItemManager.h"
#include "../../../System/ResourceManager.h"
#include"../../GameObjectParam.h"
#include"../../../System/CollisionDataManager.h"
namespace {
	const char* const kModelPath = "FireBottleModel";
	// 投げる角度のオフセット
	constexpr float kThrowOffsetRadian = 75 * MyMath::ToRadian;
	// 移動速度
	constexpr float kMoveSpeed = 1500.0f;
	// 投げる角度の最大値
	constexpr float kThrowMaxRadian = 180 * MyMath::ToRadian;
	// 効果の発動限界時間
	constexpr float kEffectMaxCount = 3.0f;
	// エフェクト透明度の最大値
	constexpr float kAlphaMax = 0.5f;
	// 攻撃のインターバル
	constexpr float kAttackInterval = 0.5f;
	// 落下速度
	constexpr float kfallSpeed = 1.0f;

	// 本体の当たり判定ID
	constexpr int kCollisionID = 210;
	// エフェクトの当たり判定ID
	constexpr int kEffectCollisionID = 211;


}
FireBottle::FireBottle()
{
	m_modelData = ResourceManager::GetInstance().GetModel(kModelPath);
	Init();
}

FireBottle::~FireBottle()
{

}

void FireBottle::Init()
{
	InitCollision();
}

void FireBottle::InitCollision()
{
	// 本体の当たり判定の追加
	CollisionParam param = CollisionDataManager::GetInstance().GetCollisionData(kCollisionID);
	AddCollision(std::make_unique<Collision::Sphere>(param.position, param.radius),CollisionType::Body);
	param = CollisionDataManager::GetInstance().GetCollisionData(kEffectCollisionID);
	AddCollision(std::make_unique<Collision::Sphere>(param.position, param.radius),CollisionType::Null);
	// エフェクトの当たり判定のパラメータをキャッシュしておく
	m_collisionParam = param;

	AddCollision(std::make_unique<Collision::AABB>(m_transform.position, Vector3::zero),CollisionType::Invalid);
}

void FireBottle::Update(float deltaTime)
{
	UpdateObject(deltaTime);
	if (m_transform.position.y < 0) {

	EffectSetup();
	}
	if (!true)return;
	UpdateEffect(deltaTime);
}

void FireBottle::End()
{

}

void FireBottle::Draw()
{
	printfDx("molotov::CollisionType : %d\n", m_collisions[0].type);
	printfDx("molotov::TileID : %d\n", GetOnTileID());
	if (true) {
		DrawEffect();
	}
	else {
		DrawModel();
	}
}
void FireBottle::DrawModel()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelData->GetHandle() == -1)return;

	MV1SetRotationXYZ(m_modelData->GetHandle(), m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelData->GetHandle(), m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelData->GetHandle());
}

void FireBottle::DrawEffect()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_alpha);
	DrawSphere3D(m_transform.position.ToVECTOR(), m_collisionParam.radius, 10, Color::kRed, Color::kRed, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

}
void FireBottle::ResolveCollision(GameObject& other, const CollisionData& myData, const CollisionData& otherData, const Collision::Result& result)
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

void FireBottle::Setup(const Transform & transform)
{
	Camera::CameraView view = ItemManager::GetInstance().GetCameraView();
	Vector3 move=(view.target - view.position).Normalize();
	Vector3 offset = Vector3::zero;
	offset.y = sinf(kThrowOffsetRadian);
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
}

void FireBottle::EffectSetup()
{
	m_moveVector = Vector3::zero;
}

void FireBottle::UpdateObject(float deltaTime)
{
	// 移動方向をキャッシュ
	Vector3 moveValue = m_moveVector * deltaTime * kMoveSpeed;
	// 座標の更新
	m_transform.position += moveValue;
	// Y軸方向(落下速度)を更新
	m_moveVector.y -= deltaTime * kfallSpeed;
	// 回転させる
	m_transform.rotation += m_rotateSpeed * deltaTime;
}

void FireBottle::UpdateEffect(float deltaTime)
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
		// 非アクティブ状態にする
		m_isActive = false;
	}


}
