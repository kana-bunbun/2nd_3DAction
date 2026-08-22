#pragma once
#include<DxLib.h>
#include<vector>
#include<memory>
#include"Input/InputConst.h"
class GamePad;
struct InputKeyParam;
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
	static bool IsDown(const Input::Action& action,const Input::GamePad& pad=Input::GamePad::None);
	static bool IsPressed(const Input::Action& action);
	static bool IsReleased(const Input::Action& action);
	static bool IsHold(const Input::Action& action);
private:
	static int GetKeyCode(const Input::Key& key);
private:
	/// <summary>
	/// ì¸óÕÇÃèÓïÒ
	/// </summary>
	static std::vector <std::unique_ptr<GamePad>>m_gamePad;
	static std::vector <InputKeyParam>m_keyParam;
	static std::vector<std::vector<Input::Key>>m_actionKey;
};