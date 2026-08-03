#include "ActionEffect_Heal.h"
#include "../../System/ActionEffectParamManager.h"
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

void ActionEffect_Heal::Init(int paramID)
{
	m_param = ActionEffectParamManager::GetInstance().GetEffectParam(paramID);
}

void ActionEffect_Heal::Draw(const Vector3& position)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(pos.ToVECTOR(), radius, 10, Color::kGreen, Color::kGreen, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

void ActionEffect_Heal::Execute(Collision::Shape* collision)
{
	pos = collision->GetPos();
	const Collision::Sphere& s = dynamic_cast<const Collision::Sphere&>(*collision);
	radius = s.GetRadius();
	// 効果範囲に触れているオブジェクトを取得
	std::vector<GameObject*>hitObjects= GameObjectManager::GetInstance().CheckHitObject(*collision);
	for (auto& objct : hitObjects) {
		// キャラクター以外はスルー
		if (!dynamic_cast<Character*>(objct))continue;
		// 回復処理を行う
		objct->Heal(m_param.power);
	}
}

