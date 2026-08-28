#pragma once
#include"Input/InputConst.h"
#include"Utility/Vector2.h"
class InputDevice {
public:
	virtual void Update(float deltaTime) = 0;
	virtual bool IsDown(int deviceKeyID) = 0;
	virtual bool IsPressed(int deviceKeyID) = 0;
	virtual bool IsReleased(int deviceKeyID) = 0;
	virtual bool IsHold(int deviceKeyID, int holdCount = Input::kHoldDefaultCount) = 0;
	virtual Vector2 GetVector(const Input::DirectionHolizontal& direction) = 0;
};