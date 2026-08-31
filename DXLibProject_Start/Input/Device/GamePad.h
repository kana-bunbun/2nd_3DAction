#pragma once
#include<array>
#include<string>
#include"InputDevice.h"
#include"Input/InputConst.h"
#include"Utility/Vector2.h"
#include"Input/Device/GamePad/GamePadState.h"

class GamePad:public InputDevice
{
public:

	GamePad(int padID=0);
	void Init();
	void Update(float deltaTime)override;
	bool IsDown(int deviceKeyID)override;
	bool IsPressed(int deviceKeyID)override;
	bool IsReleased(int deviceKeyID)override;
	bool IsHold(int deviceKeyID, int holdCount = Input::kHoldDefaultCount)override;
	Vector2 GetVector(const Input::DirectionHolizontal& direction);
	std::string GetDirectionText(DirectionFour direction);
private:
	/// <summary>
	/// 自身が調べるコントローラーの番号
	/// </summary>
	int m_padID;
	/// <summary>
	/// コントローラーの入力状態
	/// </summary>
	GamePadState m_inputState;
	std::array<std::array<float, static_cast<int>(Input::GamePadKey::Max)>,2>m_holdTime;

};
