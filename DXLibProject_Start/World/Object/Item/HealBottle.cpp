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
	// アイテム本体の当たり判定ID
	constexpr int kCollsionID = 100;
	// 回復効果の当たり判定ID
	constexpr int kEffectCollsionID = 101;
	// 回復効果のID
	constexpr int kEffectID = 0;

}

HealBottle::HealBottle()
{
	// 回転速度の初期化
	m_rotateSpeed = Vector3::zero;
	// モデルデータの取得
	m_modelData = ResourceManager::GetInstance().GetModel(kModelPath);
	m_actionEffect = new ActionEffect_Heal();
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

	// エフェクトの当たり判定のパラメータを取得
	param = CollisionDataManager::GetInstance().GetCollisionData(kEffectCollsionID);
	// エフェクトの当たり判定の追加

	m_actionEffect->SetActionEffectParam(ActionEffectParamManager::GetInstance().GetEffectParam(kEffectID));
}

void HealBottle::End()
{

}

void HealBottle::Setup(const Transform& transform)
{
	// 自身をアクティブに
	m_isActive = true;
	// ランダムな回転速度を取得
	RandomRotate();
	m_transform.rotation = m_rotateSpeed;
	// 指定座標に移動
	m_transform.position = transform.position;
	// 垂直方向に飛ばす
	m_moveVector.y = kThrowPower;
	// 発動効果を非アクティイブに
	//if (!m_actionEffect)return;
	//m_actionEffect->SetActive(true);
}

void HealBottle::Update(float deltaTime)
{
	//if(m_actionEffect)
	UpdateObject(deltaTime);
}

void HealBottle::Draw()
{
	DrawModel();
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
	default:
		break;
	}

}

void HealBottle::EffectSetup()
{
	//// 発動効果がアクティブの場合は処理しない
	//if (!m_actionEffect||
	//	m_actionEffect->IsActive())return;
	//// アクティブに設定
	//m_actionEffect->SetActive(true);
	//// 発動効果の初期化
	//m_actionEffect->Reset();
	//// 座標設定
	//m_actionEffect->SetPosition(m_transform.position);
}

void HealBottle::UpdateObject(float deltaTime)
{
	// 地面に落下したとき効果発動
	if (m_moveVector.y < 0 && m_transform.position.y < 0)
	{
		EffectSetup();
		m_isActive = false;
		return;
	}

	// 落下速度の更新
	m_moveVector.y -= deltaTime * kFallSpeed;
	// 座標更新
	m_transform.position += m_moveVector*deltaTime;
	
	// 自身を回転させる
	m_transform.rotation += m_rotateSpeed*deltaTime;

}

bool HealBottle::IsUsing()
{
	// 発動効果のポインタを持っていなかった時用
	if (!m_actionEffect)return m_isActive;

	// 自身か発動効果がアクティブの時true
	//return (m_isActive || m_actionEffect->IsActive());
}
