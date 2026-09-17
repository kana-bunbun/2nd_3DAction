#pragma once
#include "pch.h"
#include "Input/InputData.h"

class Controller
{
public:
	Controller()=default;
	virtual ~Controller()=default;
	virtual void Init() {};
	virtual void Update(float deltaTime, const InputData& _inputData)=0;
	virtual void Debug() {};
protected:
};

