#include "MolotovCocktail.h"
#include "ItemManager.h"
#include "../../../System/ResourceManager.h"
namespace {
	const char* const kModelPath = "molotovCocktail";

	constexpr float kThrowRadian = 75 * MyMath::ToRadian;
	constexpr float kMoveSpeed = 1500.0f;
	constexpr float kThrowMaxRadian = 180 * MyMath::ToRadian;
	constexpr float kEffectMaxCount = 3.0f;
	constexpr float kAlphaMax = 0.5f;
	constexpr float kEffectRadius = 300;
}
MolotovCocktail::MolotovCocktail()
{
	m_modelHandle = ResourceManager::GetInstance().GetModel(kModelPath, ResourceManager::FileName::Item);

}

MolotovCocktail::~MolotovCocktail()
{

}

void MolotovCocktail::Init()
{

}

void MolotovCocktail::Update(float deltaTime)
{
	Vector3 moveValue = m_moveVector * deltaTime * kMoveSpeed;
	m_transform.position += moveValue;
	m_moveVector.y -= deltaTime;
	m_transform.rotation += m_rotateSpeed*deltaTime;

	if (m_transform.position.y > 0)return;
	m_isEffect = true;
	m_moveVector = Vector3::zero;

	m_effectCount -= deltaTime;
	m_alpha = m_effectCount / kEffectMaxCount;
	m_alpha = MyMath::Clamp(m_alpha, 0.0f, kAlphaMax);
	if (m_effectCount < 0) {
		m_effectCount = 0;
		m_isEffect = false;
		m_isActive = false;
	}

}

void MolotovCocktail::End()
{

}

void MolotovCocktail::Draw()
{
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
	if (m_modelHandle == -1)return;

	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1DrawModel(m_modelHandle);
}

void MolotovCocktail::DrawEffect()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_alpha);
	DrawSphere3D(m_transform.position.ToVECTOR(), kEffectRadius, 10, Color::kRed, Color::kRed, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

}
void MolotovCocktail::ResolveCollision(GameObject& other, const CollisionData& myData, const CollisionData& otherData, const Collision::Result& result)
{}

void MolotovCocktail::Setup(const Transform & transform)
{
	Camera::CameraView view = ItemManager::GetInstance().GetCameraView();
	Vector3 move=(view.target - view.position).Normalize();
	Vector3 offset = Vector3::zero;
	offset.y = sinf(kThrowRadian);
	move += offset.Normalize();
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
