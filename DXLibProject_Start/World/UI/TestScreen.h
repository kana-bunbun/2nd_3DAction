#pragma once
#include"UIScreen.h"
class UIText;
class TestScreen:public UIScreen
{
public:
	enum class ScreenState {
		Invalid,
		PressStay,
		ModeSelect,
		Max
	};
public:
	TestScreen();
	~TestScreen()override=default;
	void Init()override;
	const ScreenState& GetState(){ return m_state; }
	void SetScreenState(const ScreenState& state) { m_state = state; }
	void ShowPressStay();
	void ShowModeSelect();
private:

	// 個別で処理を行うためのポインタ
	UIText* m_pLogoText;
	UIText* m_pPressText;
	UIText* m_pSelectStartText;
	UIText* m_pSelectOptionText;
	UIText* m_pSelectExitText;
	ScreenState m_state;
};

