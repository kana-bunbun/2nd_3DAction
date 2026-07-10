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

	constexpr float kEffectMaxCount = 3.0f;
	constexpr float kAlphaMax = 0.5f;
	constexpr float kEffectRadius = 420;
}

HealBottle::HealBottle() :
	m_isEffect(false),
	m_effectCount(0),
	m_alpha(0),
	m_isTrans(false)
{
	m_rotateSpeed = Vector3::zero;
	m_modelHandle = ResourceManager::GetInstance().GetModel(kModelPath, ResourceManager::FileName::Item);
	AddCollision(std::make_unique<Collision::Sphere>(m_transform.position, kEffectRadius), GameObject::CollisionType::Heal);
}

HealBottle::~HealBottle()
{
	MV1DeleteModel(m_modelHandle);
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

}

void HealBottle::Update(float deltaTime)
{
	m_transform.rotation += m_rotateSpeed * deltaTime;
	m_moveVector.y -= kFallSpeed * deltaTime;
	m_transform.position.y += m_moveVector.y * deltaTime;
	if (m_transform.position.y < 0&&m_moveVector.y<0) {
		m_moveVector.y = 0;
		m_transform.position.y = 0;
		m_isEffect = true;
	}
	m_collisions[0].type = GameObject::CollisionType::Null;
	if (!m_isEffect)return;
	m_collisions[0].type = GameObject::CollisionType::Heal;
	m_effectCount -= deltaTime;
	m_alpha = m_effectCount / kEffectMaxCount;
	m_alpha = MyMath::Clamp(m_alpha, 0.0f, kAlphaMax);
	m_isTrans = true;

	if (m_effectCount < 0) {
		m_effectCount = 0;
		m_isEffect = false;
		m_isActive = false;
	}
}

void HealBottle::Draw()
{
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
	if (m_modelHandle == -1)return;

	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelHandle);
}

void HealBottle::DrawEffect()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_alpha);
	DrawSphere3D(m_transform.position.ToVECTOR(), kEffectRadius, 10, Color::kGreen, Color::kGreen, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

}

void HealBottle::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{

}
