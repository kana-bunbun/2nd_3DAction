#pragma once
#include"Input/InputConst.h"
#include"Input/ActionInputState.h"
#include<array>
/// <summary>
/// Še‰æ–Êó‘Ô‚É“n‚·“ü—Íî•ñ
/// </summary>
class InputData
{
public:
	InputData();
	void Init(std::array<ActionInputState, static_cast<int>(Input::Action::Max)>inputState);
	bool IsDown(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsDown(); }
	bool IsPressed(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsPressed(); }
	bool IsReleased(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsReleased(); }
	bool IsHold(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsHold(); }
private:
	std::array<ActionInputState,static_cast<int>(Input::Action::Max)> m_actionInputState;
};

