#include "Stair.h"
#include"../Map/MapManager.h"
#include"../UI/BillboardManager.h"
namespace {
	constexpr Vector3 kBillboardOffset = { 0.0f,100.0f,0.0f };
	constexpr Vector3 kCollisionSize = { MapConst::kTileSize*2,MapConst::kTileSize,MapConst::kTileSize * 2 };
	constexpr Vector3 kModelOffset = { 0.0f,-MapConst::kFloorScale* kCollisionSize.y,0.0f };

	const char* const kFilePath = "Resource\\Map\\stairs.mv1";
	constexpr float kAlphaSpeed = 255.0f * 3.0f;
}
Stair::Stair():
	m_isHitOld(false),
	m_isHit(false),
	m_alpha(0),
	m_pad(Input::Pad::Invalid),
	m_billboardPos(Vector3::zero)
{
	m_transform.Reset();
	//m_collision = std::make_unique<Collision::AABB>(Vector3::zero, kCollisionSize);
	AddCollision(std::make_unique<Collision::AABB>(Vector3::zero, kCollisionSize), GameObject::CollisionType::Body);
	m_modelHandle = MV1LoadModel(kFilePath);
	// 読み込んだ値を元にエミッシブカラーを設定
	COLOR_F color = { 0.3f,0.3f,0.3f,1.0f };
	MV1SetMaterialEmiColor(m_modelHandle, 0, color);
	float sizeAxis = MapConst::kFloorScale;
	Vector3 size = { sizeAxis,sizeAxis ,sizeAxis };
	MV1SetScale(m_modelHandle, size.ToVECTOR());
}

Stair::~Stair()
{
	MV1DeleteModel(m_modelHandle);
}

void Stair::Init()
{

}

void Stair::Update(float deltaTime)
{
	m_isHitOld = m_isHit;
	// アルファ値の増減量を求める
	float alphaValue = kAlphaSpeed * deltaTime ;
	if (m_isHitOld) {	// プレイヤーが当たっているときアルファ値増加
		m_alpha += alphaValue;
	}
	else {			// プレイヤーが当たっていないときアルファ値減少
		m_alpha -= alphaValue;
	}
	// アルファ値を値域内に収める
	m_alpha = MyMath::Clamp(m_alpha, 0.0f, 255.0f);
	m_isHit = false;
}

void Stair::Draw()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelHandle != -1) {
		Vector3 position = m_transform.position + kModelOffset;
		MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
		MV1SetPosition(m_modelHandle, position.ToVECTOR());
		MV1DrawModel(m_modelHandle);
	}
}

void Stair::ResolveCollision(GameObject & other, const Collision::Result & result)
{

}

void Stair::ResolveCollision(GameObject::CollisionTag tag, const Collision::Result& result)
{}

void Stair::ResolveCollision(GameObject & other, const CollisionData & myData, const CollisionData & otherData, const Collision::Result & result)
{
	switch (other.GetCollisionTag())
	{
	case CollisionTag::Player:
		m_isHit = true;
		m_billboardPos = other.GetTransform().position;
	default:
		break;
	}
}

void Stair::LateDraw()
{
	Vector3 billboardPos = m_billboardPos + kBillboardOffset;
	// 透明度を操作して描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	// ビルボードで描画
	BillboardManager::GetInstance().DrawBillboard(billboardPos, -0.2f, 0, 300, 0, BillboardManager::eBillboard::Stair);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Stair::SetTile(int tileID)
{
	m_transform.position = MapManager::GetInstance().GetWorldPosFromID(tileID);
	
}
