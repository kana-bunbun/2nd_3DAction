#pragma once
#include<DxLib.h>
#include<array>
#include"InputDevice.h"
#include"Utility/Vector2.h"
class GamePadState;
class GamePad:public InputDevice
{
public:

	GamePad(int padID=0);
	void Init();
	void Update(float deltaTime)override;
	int GetKeyCode(const Input::Key& key)override;
	bool IsDown(const Input::Key& key)override;
	bool IsPressed(const Input::Key& key)override;
	bool IsReleased(const Input::Key& key)override;
	bool IsHold(const Input::Key& key, int holdCount = Input::kHoldDefaultCount)override;
	Vector2 AnalogInput(const Input::Thumb& thumb);
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

/// <summary>
/// スティックの入力情報
/// </summary>
class InputThumb {
public:
	InputThumb(int holizontal=0, int vertical=0);
	/// <summary>
	/// 傾けた量
	/// </summary>
	Vector2 tilt;
	/// <summary>
	/// 入力角度
	/// </summary>
	float tiltRadian;
	/// <summary>
	/// 入力量
	/// </summary>
	float tiltRatio;
	/// <summary>
	/// 4方向の入力方向
	/// </summary>
	Input::DirectionFour directionFour;
	/// <summary>
	/// 8方向
	/// </summary>
	Input::DirectionEight directionEight;
};
/// <summary>
/// トリガーの入力情報
/// </summary>
class InputTrigger {
public:
	InputTrigger(int input=0);
	/// <summary>
	/// 入力量
	/// </summary>
	float inputRatio;
};
class GamePadState {
public:
	GamePadState(const XINPUT_STATE& inputState = XINPUT_STATE());
	InputThumb leftThumb;
	InputThumb rightThumb;
	InputTrigger rightTrigger;
	InputTrigger leftTrigger;
	std::array<bool, static_cast<int>(Input::GamePadKey::Max)> isKeyDown;
};