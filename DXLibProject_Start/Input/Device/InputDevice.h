#pragma once
#include"Input/InputConst.h"
#include"Utility/Vector2.h"
#include"Input/VectorState.h"
class InputDevice {
public:
	virtual void Update(float deltaTime) = 0;
	virtual bool IsDown(int deviceKeyID) = 0;
	virtual bool IsPressed(int deviceKeyID) = 0;
	virtual bool IsReleased(int deviceKeyID) = 0;
	virtual bool IsHold(int deviceKeyID, int holdCount = Input::kHoldDefaultCount) = 0;
	virtual VectorState GetVectorState(int deviceKeyID) = 0;
};