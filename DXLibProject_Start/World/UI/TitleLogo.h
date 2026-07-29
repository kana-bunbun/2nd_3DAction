#pragma once
#include<string>
#include"../../Utility/Vector3.h"
#include"UIObject.h"
class TitleLogo:public UIObject
{
public:
	TitleLogo();
	~TitleLogo() = default;
	
	void OnInit()override;
	void OnEnd()override;
	void OnUpdate(float deltaTime)override;
	void OnDraw()override;

	
private:

	/// <summary>
	/// 描画する文字列
	/// </summary>
	std::string m_text;
};

