#include "ActionEffect_Heal.h"
#include"../GameObjectManager.h"
namespace {
	constexpr float kAlphaMax = 0.5f;
}
ActionEffect_Heal::ActionEffect_Heal()
{
	m_executeCount = 0.0f;
}

ActionEffect_Heal::~ActionEffect_Heal()
{

}

void ActionEffect_Heal::Init()
{

}

void ActionEffect_Heal::End()
{

}

void ActionEffect_Heal::Update(float deltaTime)
{
	// カウントダウン
	m_effectCount -= deltaTime;
	// カウントに応じて透明度を求める
	m_alpha = m_effectCount / m_param.maxSecond;
	// 透明度をクランプ
	m_alpha = MyMath::Clamp(m_alpha, 0.0f, kAlphaMax);
	// 透明度フラグの更新
	m_isTrans = true;
	// 効果発動のカウントを更新
	m_executeCount += deltaTime;
	// 効果カウントがインターバルを超えたら
	if (m_executeCount > m_param.interval) {
		m_executeCount = 0;
	}

	// カウントが0になったら
	if (m_effectCount <= 0) {
		// カウントを0に
		m_effectCount = 0;
		// 非アクティブにする
		m_isActive = false;
	}
}

void ActionEffect_Heal::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * m_alpha);
	DrawSphere3D(m_transform.position.ToVECTOR(), m_collisionParam.radius, 10, Color::kGreen, Color::kGreen, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

void ActionEffect_Heal::Reset()
{
	m_executeCount = 0.0f;
	m_effectCount = m_param.maxSecond;
}

void ActionEffect_Heal::Execute()
{
	std::vector<GameObject*>hitObjects= GameObjectManager::GetInstance().CheckHitObject(*m_collisions[0].shape);
	for (auto& objct : hitObjects) {
		objct->Damage(m_param.power);
	}
}

