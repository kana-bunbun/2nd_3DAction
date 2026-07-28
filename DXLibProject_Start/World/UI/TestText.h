#pragma once
#include<string>
#include"../../Utility/Vector3.h"
#include"UIObject.h"
class TestText:public UIObject
{
public:
	TestText();
	~TestText()=default;
	void Init()override;
	void Update(float deltaTime)override;
	void Draw()override;
	void End()override;
private:
	std::string m_text;
	float m_blinkTimer;
};

