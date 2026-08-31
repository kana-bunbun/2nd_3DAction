#pragma once
#include"Input/InputConst.h"
class ActionInputState {
public:
	ActionInputState()=default;
	ActionInputState(bool isDown, bool isPressed, bool isReleased, bool isHold);
	bool IsDown() { return m_isDown; }
	bool IsPressed() { return m_isPressed; }
	bool IsReleased() { return m_isReleased; }
	bool IsHold() { return m_isHold; }
private:
	bool m_isDown = false;
	bool m_isPressed = false;
	bool m_isReleased = false;
	bool m_isHold = false;

};