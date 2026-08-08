#pragma once
#include"Utility/Input.h"
#include<unordered_map>
struct UIInputKey;
struct UIInputKey {
	enum State {
		CurrentState,
		PrevState,
		Max
	};
	/// <summary>
	/// 押しているかどうか取得
	/// </summary>
	bool IsDown() { return keyState[State::CurrentState]; }
	/// <summary>
	/// 押した瞬間かどうか取得
	/// </summary>
	bool IsPressed() { return keyState[State::CurrentState] && !keyState[State::PrevState]; }
	/// <summary>
	/// 離した瞬間かどうか取得
	/// </summary>
	bool IsReleased() { return !keyState[State::CurrentState] && keyState[State::PrevState]; }

	//bool IsHold() { return Input:: }

	bool keyState[State::Max] = { false,false };

};
/// <summary>
/// Sceneで入力した結果を構造体にまとめる
/// その結果をUIに渡すことで入力処理をUIに持たせず処理させることができる
/// </summary>

struct UIInput
{
	enum class Key {
		Up,
		Right,
		Down,
		Left,
		Decide,
		Cancel,
		Menu,
		Max,
	};
public:
	UIInputKey keys[static_cast<int>(Key::Max)];
	bool IsDown(const Key& key) { return keys[static_cast<int>(key)].IsDown(); }
	bool IsPressed(const Key& key) { return keys[static_cast<int>(key)].IsPressed(); }
	bool IsReleased(const Key& key) { return keys[static_cast<int>(key)].IsReleased(); }
	//bool IsHold(const Key& key) { return keys[static_cast<int>(key)].IsReleased(); }
public:
};

