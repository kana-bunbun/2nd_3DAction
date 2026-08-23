#pragma once
#include<DxLib.h>
#include<vector>
#include<memory>
#include"Input/InputConst.h"
class GamePad;
struct InputKeyParam;
struct ActionKeyParam;
class InputManager
{
public:
	InputManager();
	static void Init();
	static void End();
	static void Update(float deltaTime);
	static bool IsDown (const Input::Key& key, const Input::GamePad& pad);
	static bool IsPressed(const Input::Key& key, const Input::GamePad& pad);
	static bool IsReleased(const Input::Key& key, const Input::GamePad& pad);
	static bool IsHold(const Input::Key& key, const Input::GamePad& pad);
	static bool IsDown(const Input::Action& action,const Input::GamePad& pad=Input::GamePad::None);
	static bool IsPressed(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::None);
	static bool IsReleased(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::None);
	static bool IsHold(const Input::Action& action, const Input::GamePad& pad = Input::GamePad::None);
private:
	static int GetKeyCode(const Input::Key& key);
private:
	/// <summary>
	/// 入力の情報
	/// </summary>
	static std::vector <std::unique_ptr<GamePad>>m_gamePad;
	/// <summary>
	/// キーの情報
	/// </summary>
	static std::vector <InputKeyParam>m_keyParam;
	/// <summary>
	/// アクションごとのキー情報
	/// </summary>
	static std::vector<ActionKeyParam>m_actionParam;
};