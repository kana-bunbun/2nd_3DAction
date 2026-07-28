#pragma once
#include"ActionEffectBase.h"
class ActionEffect_Heal:public ActionEffectBase
{
public:
	ActionEffect_Heal();
	~ActionEffect_Heal();

	void Init();
	void Update(float deltaTime);
	void Draw(const Vector3& position);
	void Reset();
	void Execute(Collision::Shape* collision)override;

	bool IsTransparent() { return m_isTrans; }
public:
	float m_alpha;
	bool m_isTrans;
};

