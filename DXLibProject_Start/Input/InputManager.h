#pragma once
#include"pch.h"

#include"Input/InputConst.h"
#include"Input/InputData.h"
class GamePad;
struct InputKeyParam;
struct ActionKeyParam;
struct VectorState;
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
	static Vector2 GetVector(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::Pad1);
	static Vector2 GetVector(const Input::Key& key, const Input::GamePad& pad);
	static const InputData GetInputData();
private:
	static void UpdateInputData();
	static VectorState GetVectorState(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::Pad1);
	static VectorState GetVectorState(const Input::Key& key, const Input::GamePad& pad);
private:
};
