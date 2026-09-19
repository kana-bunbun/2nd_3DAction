#include"pch.h"
#include "ActionEffect_Heal.h"
#include "../../System/ActionEffectParamManager.h"
#include"../GameObjectManager.h"
#include"../Character/Character.h"
#include"System/EffectManager.h"
namespace {
	constexpr float kAlphaMax = 0.5f;
}
ActionEffect_Heal::ActionEffect_Heal():
	m_alpha(0.0f)
{
}

ActionEffect_Heal::~ActionEffect_Heal()
{

}

void ActionEffect_Heal::Init(int paramID)
{
	m_param = ActionEffectParamManager::GetInstance().GetEffectParam(paramID);
}

void ActionEffect_Heal::Start()
{
}

void ActionEffect_Heal::Draw()
{
	
}

void ActionEffect_Heal::Execute(Collision::ICollider* collision)
{
	// 効果範囲に触れているオブジェクトを取得
	std::vector<GameObject*>hitObjects = GameObjectManager::GetInstance().CheckHitObject(*collision);
	for (auto& objct : hitObjects) {
		// キャラクター以外はスルー
		if (!dynamic_cast<Character*>(objct))continue;
		// 回復処理を行う
		objct->Heal(m_param.value);
	}
}

