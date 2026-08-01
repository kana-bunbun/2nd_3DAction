#pragma once
#include"../UIScreen.h"
class UIButton;
class IngameHudScreen :public UIScreen
{
	IngameHudScreen();
	~IngameHudScreen()override = default;

	void Init()override;
private:
	UIButton* m_pButton;
};

