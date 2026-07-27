#include "HealBottle.h"
#include "../../../System/ResourceManager.h"
#include "../../../System/CollisionDataManager.h"
#include"../../../Utility/MyRandom.h"
#include"../../GameObjectManager.h"
#include"../../../World/Action/ActionEffect_Heal.h"
#include"../../../System/ActionEffectParamManager.h"
namespace {
	const char* const kModelPath = "HealBottleModel";

	// 投げる力の強さ
	constexpr float kThrowPower=1200.0f;
	// 落下速度
	constexpr float kFallSpeed = kThrowPower *2.5f;

	// 効果発動の最大カウント
	constexpr float kEffectMaxCount = 3.0f;
	// 透明度の最大値
	constexpr float kAlphaMax = 0.5f;
	// 回復効果発動インターバル
	constexpr float kEffectInterval = 0.3f;
	// 回復効果の当たり判定ID
	constexpr int kEffectCollsionID = 100;
	// アイテム本体の当たり判定ID
	constexpr int kCollsionID = 101;
	// 回復効果のID
	constexpr int kEffectID = 0;

}

HealBottle::HealBottle() :
	m_alpha(0),
	m_isEffect(false)
{
	// 回転速度の初期化
	m_rotateSpeed = Vector3::zero;
	// モデルデータの取得
	m_modelData = ResourceManager::GetInstance().GetModel(kModelPath);
	m_actionEffect = GameObjectManager::GetInstance().CreateObject<ActionEffect_Heal>();
	Init();

}

HealBottle::~HealBottle()
{
	delete m_modelData;
	m_modelData = nullptr;
}

void HealBottle::Init()
{
	// 当たり判定の初期設定
	InitCollision();
}

void HealBottle::InitCollision()
{
	// 本体の当たり判定の追加
	CollisionParam param = CollisionDataManager::GetInstance().GetCollisionData(kCollsionID);
	AddCollision(std::make_unique<Collision::Sphere>(param.position, param.radius), CollisionType::Body);
	// エフェクトの当たり判定の追加
	param = CollisionDataManager::GetInstance().GetCollisionData(kEffectCollsionID);
	AddCollision(std::make_unique<Collision::Sphere>(param.position, param.radius), CollisionType::Body);

	// エフェクトの当たり判定のパラメータをキャッシュしておく
	m_collisionParam = param;
	m_actionEffect->SetCollision(m_collisions[1].shape.get());
	m_actionEffect->SetCollisionParam(param);
	m_actionEffect->SetActionEffectParam(ActionEffectParamManager::GetInstance().GetEffectParam(kEffectID));
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

	m_actionEffect->SetActive(false);
	m_effectCount = kEffectMaxCount;

	m_isEffect = false;

}

void HealBottle::Update(float deltaTime)
{
	m_isActive = false;
	if (m_transform.position.y <= 0 && m_moveVector.y < 0)return;
	m_isActive = true;
	// 効果発動前の処理
	BeforeEffectUpdate(deltaTime);


}

void HealBottle::Draw()
{
	printfDx("healBottle::CollisionType : %d\n", m_collisions[0].type);
	printfDx("healBottle::TileID : %d\n", GetOnTileID());
	if (!m_isEffect) {
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
	if (m_isEffect)return;
	// 落下速度を0に
	m_moveVector.y = 0;
	// Y座標をクランプ
	m_transform.position.y = MyMath::Clamp(m_transform.position.y, 0.0f, m_transform.position.y);
	// アクティブに設定
	m_actionEffect->SetActive(true);
	m_actionEffect->Reset();
	m_actionEffect->SetPosition(m_transform.position);
	m_isEffect = true;
}

void HealBottle::BeforeEffectUpdate(float deltaTime)
{
	// 効果発動中なら処理しない
	if (m_actionEffect->IsActive())return;
	// 回転させる
	m_transform.rotation += m_rotateSpeed * deltaTime;
	// 落下速度を更新
	m_moveVector.y -= kFallSpeed * deltaTime;
	// 落下させる
	m_transform.position.y += m_moveVector.y * deltaTime;
	// 効果発動前は衝突判定をチェックしない
	m_collisions[0].type = CollisionType::Null;
	// 地面に落下した時
	if (m_transform.position.y < 0 && m_moveVector.y < 0) {
		// 効果のセットアップ
		EffectSetup();

	}
}
