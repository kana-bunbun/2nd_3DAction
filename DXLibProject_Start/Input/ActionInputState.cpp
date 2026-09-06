#include"pch.h"
#include "ActionInputState.h"
ActionInputState::ActionInputState(bool isDown, bool isPressed, bool isReleased, bool isHold):
	m_isDown(isDown),
	m_isPressed(isPressed),
	m_isReleased(isReleased),
	m_isHold(isHold)
{
}
