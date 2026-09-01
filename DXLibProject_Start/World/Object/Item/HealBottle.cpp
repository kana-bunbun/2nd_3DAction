#include "HealBottle.h"
#include "../../../System/ResourceManager.h"
#include "../../../System/CollisionDataManager.h"
#include"../../../Utility/MyRandom.h"
#include"../../GameObjectManager.h"
#include"../../../World/Action/ActionEffect_Heal.h"
#include"../../../System/ActionEffectParamManager.h"
#include"../../../System/ActionParamManager.h"
#include"../../../System/ActionIntervalParamManager.h"
namespace {
	const char* const kModelPath = "HealBottleModel";

	// 投げる力の強さ
	constexpr float kThrowPower=1200.0f;
	// 落下速度
	constexpr float kFallSpeed = kThrowPower *2.5f;

	// アイテム自身の当たり判定
	constexpr int kCollisionID = 100;
	// 透明度の最大値
	constexpr float kAlphaMax = 0.5f;
	// 回復効果のID
	constexpr int kEffectID = 0;

}

HealBottle::HealBottle()
{
	// 回転速度の初期化
	m_rotateSpeed = Vector3::zero;
	// モデルデータの取得
	m_modelData = ResourceManager::GetInstance().GetModel(kModelPath);
	Init();
	// 本体の当たり判定の追加
	CollisionParam param= CollisionDataManager::GetInstance().GetCollisionData(kCollisionID);
	AddCollision(std::make_unique<Collision::Sphere>(param.position, param.radius), CollisionType::Body);

}

HealBottle::~HealBottle()
{
	delete m_modelData;
	m_modelData = nullptr;
}

void HealBottle::Init()
{
	// パラメータの初期設定
	InitParameter();
}

void HealBottle::InitParameter()
{
	// 発動効果のパラメータ読み込み
	m_actionParam = ActionParamManager::GetInstance().GetActionParam(kEffectID);
	// 発動効果の当たり判定追加
	m_pEffectCollision=std::move(CollisionDataManager::GetInstance().GetCollision(m_actionParam.collisionID));
	// 発動効果の効果量を追加
	m_pActionEffect = std::make_unique<ActionEffect_Heal>();
	m_pActionEffect->Init(m_actionParam.effectID);
	// 効果の発動インターバルパラメータ追加
	m_pInterval = std::make_unique<ActionInterval>();
	m_pInterval->Init(m_actionParam.intervalID);
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
	m_pInterval->Setup();
	// 発動効果を非アクティイブに
	//if (!m_actionEffect)return;
	//m_actionEffect->SetActive(true);
}

void HealBottle::Update(float deltaTime,const InputData& inputData)
{
	IntervalUpdate(deltaTime);
	UpdateObject(deltaTime);
	m_pEffectCollision->SetPosition(m_transform.position);

}

void HealBottle::Draw()
{
	DrawModel();
	m_pActionEffect->Draw(m_transform.position);
}

void HealBottle::DrawModel()
{
	// モデルが読み込まれているかどうかチェック
	if (m_modelData->GetHandle() == -1)return;
	if (m_pInterval->IsActive())return;
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
	// 座標設定
	m_pEffectCollision->SetPosition(m_transform.position);
	// インターバルをアクティブに設定
	m_pInterval->SetActive(true);
}

void HealBottle::UpdateObject(float deltaTime)
{
	// 地面に落下したとき効果発動
	if (m_moveVector.y < 0 && m_transform.position.y < 0)
	{
		EffectSetup();
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
	// インターバルを持っていなかった時用
	if (!m_pInterval)return m_isActive;

	// 自身かインターバルがアクティブの時true
	return (m_isActive || m_pInterval->IsActive());
}
