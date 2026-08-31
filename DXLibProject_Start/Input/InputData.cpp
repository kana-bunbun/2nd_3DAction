#include "InputData.h"

InputData::InputData():
	m_actionInputState()
{
}

void InputData::Init(std::array<ActionInputState, static_cast<int>(Input::Action::Max)> inputState)
{
	m_actionInputState = inputState;
}


