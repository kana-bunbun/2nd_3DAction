#pragma once
#include"../GameObject.h"
#include"../../Data/ActionEffectParam.h"
#include"../Component/Collision.h"

class ActionEffectBase
{
public:
	ActionEffectBase() = default;
	~ActionEffectBase() = default;

	virtual void Execute(Collision::Shape* collision) = 0;
	void SetActionEffectParam(const ActionEffectParam& param) { m_param = param; }
protected:
	// 効果のパラメータ
	ActionEffectParam m_param;
};

