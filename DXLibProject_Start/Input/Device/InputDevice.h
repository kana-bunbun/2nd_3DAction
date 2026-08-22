#pragma once
#include"Input/InputConst.h"
class InputDevice {
public:
	virtual void Update(float deltaTime) = 0;
	virtual int GetKeyCode(const Input::Key& key) = 0;
	virtual bool IsDown(const Input::Key& key) = 0;
	virtual bool IsPressed(const Input::Key& key) = 0;
	virtual bool IsReleased(const Input::Key& key) = 0;
	virtual bool IsHold(const Input::Key& key, int holdCount = Input::kHoldDefaultCount) = 0;
}