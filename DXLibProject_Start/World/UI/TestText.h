#pragma once
#include<string>
#include"../../Utility/Vector3.h"
#include"UIObject.h"
class TestText:public UIObject
{
public:
	TestText();
	~TestText()=default;
	void OnInit()override;
	void OnUpdate(float deltaTime)override;
	void OnDraw()override;
	void OnEnd()override;
private:
	std::string m_text;
	float m_blinkTimer;
};

