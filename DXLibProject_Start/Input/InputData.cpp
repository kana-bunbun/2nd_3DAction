#include "InputData.h"
#include"VectorState.h"
InputData::InputData():
	m_actionInputState(),
	m_vectorState()
{
}

void InputData::Init(std::array<ActionInputState, static_cast<int>(Input::Action::Max)> inputState, std::array<VectorState, static_cast<int>(Input::Action::Max)> vectorState)
{
	m_actionInputState = inputState;
	this->m_vectorState= vectorState;
}

const Vector2 InputData::GetVector(const Input::Action& action) 
{
	int actionID = static_cast<int>(action);
	return m_vectorState[actionID].GetVector();
}

float InputData::GetRadian(const Input::Action& action) 
{
	int actionID = static_cast<int>(action);
	return m_vectorState[actionID].GetRadian();
}

float InputData::GetInputRatio(const Input::Action& action) 
{
	int actionID = static_cast<int>(action);
	return m_vectorState[actionID].GetRatio();
}


