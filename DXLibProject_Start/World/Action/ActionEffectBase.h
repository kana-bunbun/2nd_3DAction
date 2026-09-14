#pragma once
#include"../GameObject.h"
#include"../../Data/ActionEffectParam.h"
#include"World/Component/Collision/Collision.h"
#include"World/Component/Collision/ICollider.h"

class ActionEffectBase
{
public:
	ActionEffectBase() = default;
	~ActionEffectBase() = default;
	virtual void Init(int paramID)=0;
	virtual void Draw()=0;
	virtual void Start() {};

	virtual void Execute(Collision::ICollider* collision) = 0;
	void SetActionEffectParam(const ActionEffectParam& param) { m_param = param; }
protected:
	// 効果のパラメータ
	ActionEffectParam m_param;
};

