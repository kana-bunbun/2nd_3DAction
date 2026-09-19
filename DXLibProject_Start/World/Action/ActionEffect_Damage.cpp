#include "pch.h"
#include "ActionEffect_Damage.h"
#include "../../System/ActionEffectParamManager.h"
#include"../GameObjectManager.h"
#include"../Character/Character.h"
#include"System/EffectManager.h"
namespace {
	constexpr float kAlphaMax = 0.5f;
}
ActionEffect_Damage::ActionEffect_Damage() :
	m_alpha(0.0f)
{}

ActionEffect_Damage::~ActionEffect_Damage()
{

}

void ActionEffect_Damage::Init(int paramID)
{
	m_param = ActionEffectParamManager::GetInstance().GetEffectParam(paramID);
}

void ActionEffect_Damage::Start()
{}

void ActionEffect_Damage::Draw()
{

}

void ActionEffect_Damage::Execute(Collision::ICollider* collision)
{
	// 効果範囲に触れているオブジェクトを取得
	std::vector<GameObject*>hitObjects = GameObjectManager::GetInstance().CheckHitObject(*collision);
	for (auto& objct : hitObjects) {
		bool isCharacter = !dynamic_cast<Character*>(objct);
		// キャラクター以外はスルー
		if (isCharacter)continue;
		// ダメージ処理を行う
		objct->Damage(m_param.value);
	}
}


