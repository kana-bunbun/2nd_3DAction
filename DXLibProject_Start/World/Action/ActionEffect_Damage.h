#pragma once
#include"ActionEffectBase.h"
class ActionEffect_Damage:public ActionEffectBase
{
public:
	ActionEffect_Damage();
	~ActionEffect_Damage();

	void Init(int paramID)override;
	void Start()override;
	void Draw()override;
	void Reset();
	void Execute(Collision::ICollider* collision)override;

public:
	float m_alpha;
};

