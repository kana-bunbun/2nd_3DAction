#include "ActionEffect_Heal.h"
#include"../GameObjectManager.h"
#include"../Character/Character.h"
namespace {
	constexpr float kAlphaMax = 0.5f;
}
ActionEffect_Heal::ActionEffect_Heal():
	m_alpha(0.0f),
	m_isTrans(true)
{
}

ActionEffect_Heal::~ActionEffect_Heal()
{

}


void ActionEffect_Heal::Update(float deltaTime)
{
	//// カウントダウン
	//m_effectCount -= deltaTime;
	//// カウントに応じて透明度を求める
	//m_alpha = m_effectCount / m_param.maxSecond;
	//// 透明度をクランプ
	//m_alpha = MyMath::Clamp(m_alpha, 0.0f, kAlphaMax);
	//// 透明度フラグの更新
	//m_isTrans = true;
	//// 効果発動のカウントを更新
	//m_executeCount += deltaTime;
	//// 効果カウントがインターバルを超えたら
	//if (m_executeCount > m_param.interval) {
	//	m_executeCount = 0;
	//	Execute();
	//}

	//// カウントが0になったら
	//if (m_effectCount <= 0) {
	//	// カウントを0に
	//	m_effectCount = 0;
	//	// 非アクティブにする
	//	m_isActive = false;
	//}
	//m_collision->SetPosition(m_transform.position);
}

void ActionEffect_Heal::Draw(const Vector3& position)
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0f * m_alpha));
	//DrawSphere3D(m_transform.position.ToVECTOR(), m_collisionParam.radius, 10, Color::kGreen, Color::kGreen, TRUE);
	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

void ActionEffect_Heal::Execute(Collision::Shape* collision)
{
	// 効果範囲に触れているオブジェクトを取得
	std::vector<GameObject*>hitObjects= GameObjectManager::GetInstance().CheckHitObject(*collision);
	for (auto& objct : hitObjects) {
		// キャラクター以外はスルー
		if (!dynamic_cast<Character*>(objct))continue;
		// 回復処理を行う
		objct->Heal(m_param.power);
	}
}

