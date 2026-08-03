#pragma once
#include"../Core/UIScreen.h"
class UIButton;
class IngameHudScreen :public UIScreen
{
public:
	IngameHudScreen();
	~IngameHudScreen()override = default;

	void Init()override;
private:
	UIButton* m_pButton;
};

