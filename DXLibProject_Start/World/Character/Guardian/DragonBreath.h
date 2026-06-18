#pragma once
#include"../../Component/Transform.h"

class DragonBreath
{
public:
	DragonBreath();
	~DragonBreath();

	void Init(const Transform& transform);
	void End();
	void Update(float deltaTime);
	void Draw();

private:
	Transform m_transform;
	bool m_isActive;
};

