#pragma once
#include"ActionEffectBase.h"
class ActionEffect_Heal:public ActionEffectBase
{
public:
	ActionEffect_Heal();
	~ActionEffect_Heal();

	void Init(int paramID)override;
	void Start()override;
	void Draw()override;
	void Reset();
	void Execute(Collision::ICollider* collision)override;

public:
	float m_alpha;
};

