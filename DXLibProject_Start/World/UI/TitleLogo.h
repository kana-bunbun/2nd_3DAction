#pragma once
#include<string>
#include"../../Utility/Vector3.h"
#include"UIObject.h"
class TitleLogo:public UIObject
{
public:
	TitleLogo();
	~TitleLogo() = default;
	
	void Init()override;
	void End()override;
	void Update(float deltaTime)override;
	void Draw()override;

	
private:

	/// <summary>
	/// 描画する文字列
	/// </summary>
	std::string m_text;
};

