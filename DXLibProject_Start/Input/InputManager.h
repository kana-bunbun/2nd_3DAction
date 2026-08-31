#pragma once
#include<DxLib.h>
#include<vector>
#include<memory>
#include"Input/InputConst.h"
#include"Input/InputData.h"
class GamePad;
struct InputKeyParam;
struct ActionKeyParam;
class InputManager
{
public:
	static void Init();
	static void End();
	static void Update(float deltaTime);
	static bool IsDown (const Input::Key& key, const Input::GamePad& pad);
	static bool IsPressed(const Input::Key& key, const Input::GamePad& pad);
	static bool IsReleased(const Input::Key& key, const Input::GamePad& pad);
	static bool IsHold(const Input::Key& key, const Input::GamePad& pad);
	static bool IsDown(const Input::Action& action,const Input::GamePad& pad=Input::GamePad::Pad1);
	static bool IsPressed(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::Pad1);
	static bool IsReleased(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::Pad1);
	static bool IsHold(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::Pad1);
	static const InputData GetInputData();
private:
	static void UpdateInputData();
private:
};