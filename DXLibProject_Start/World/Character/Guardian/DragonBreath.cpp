#include "DragonBreath.h"
#include "../../../Utility/Color.h"
#include"../../../System/TimeManager.h"
#include"../CharacterManager.h"
namespace {
	constexpr float kMoveSpeed = 500.0f;
	constexpr float kDeleteCount = 3.0f;
	constexpr float kSphereRadius = 30;
}
DragonBreath::DragonBreath()
{
	m_transform.Reset();
	AddCollision(std::make_unique<Collision::Sphere>(m_transform.position, kSphereRadius), CollisionType::Attack);
}

DragonBreath::~DragonBreath()
{

}

void DragonBreath::Init()
{

}

void DragonBreath::Setup(const Vector3& RegistPos, const Vector3& moveVec)
{
	// 生成座標の設定
	m_transform.position = RegistPos;
	// 当たり判定の更新
	UpdateCollision();
	// 移動方向のノーマライズ
	m_moveVec = moveVec.Normalize();
	// アクティブフラグをtrue
	m_isActive = true;
	// 生存時間の初期化
	m_lifeCount = 0.0f;
}


void DragonBreath::Update(float deltaTime)
{
	//deltaTime = 0.0000001f;

	m_transform.position += m_moveVec * kMoveSpeed * deltaTime;
	m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
	m_lifeCount += deltaTime;

	// 生成されてから一定時間たつと削除
	if (m_lifeCount < kDeleteCount)return;
	m_isActive = false;

	m_collisions[0].shape->SetPosition(m_transform.position);
	//for (int i = 0; i < m_hitData.size(); i++) {

	//	m_hitData[i].isHit = false;
	//}

}

void DragonBreath::Draw()
{
	DrawSphere3D(m_transform.position.ToVECTOR(), kSphereRadius, 10, Color::kMagenta, Color::kMagenta, TRUE);
}

void DragonBreath::ResolveCollision(GameObject& other, const CollisionData& myData, const CollisionData& otherData, const Collision::Result& result)
{
	switch (other.GetCollisionTag())
	{
	case CollisionTag::Enemy: {
		
		if (IsCollisionEnter(otherData.shape.get())) {
		const Character& character = dynamic_cast<const Character&>(other);
		Character* Enemy=CharacterManager::GetInstance().GetCharacter(character.m_ID);
		if (!Enemy)break;
		Enemy->Damage(5);
		GameObject::HitCollisionData data = { otherData.shape.get(),true};
		m_hitData.push_back(data);
		}
		break;
	}
	default:
		break;
	}
}
