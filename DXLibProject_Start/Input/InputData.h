#pragma once
#include"pch.h"

#include"Input/InputConst.h"
#include"Input/ActionInputState.h"
#include"Utility/Vector2.h"
#include"VectorState.h"
/// <summary>
/// Še‰æ–Êó‘Ô‚É“n‚·“ü—Íî•ñ
/// </summary>
class InputData
{
public:
	InputData();
	void Init(std::array<ActionInputState, static_cast<int>(Input::Action::Max)>inputState, std::array<VectorState, static_cast<int>(Input::Action::Max)> vector);
	bool IsDown(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsDown(); }
	bool IsPressed(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsPressed(); }
	bool IsReleased(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsReleased(); }
	bool IsHold(const Input::Action& action) { return m_actionInputState[static_cast<int>(action)].IsHold(); }
	const Vector2 GetVector(const Input::Action& action);
	float GetRadian(const Input::Action& action);
	float GetInputRatio(const Input::Action& action);
private:
	std::array<ActionInputState,static_cast<int>(Input::Action::Max)> m_actionInputState;
	std::array<VectorState, static_cast<int>(Input::Action::Max)> m_vectorState;
};

