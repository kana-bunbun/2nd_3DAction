#pragma once
namespace UIInputState {
	enum {
		IsDown,			// 押しているかどうか
		IsPressed,		// 押した瞬間
		IsReleased,		// 離した瞬間
		IsHold,			// 長押し状態
		Max,
	};
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
}
/// <summary>
/// Sceneで入力した結果を構造体にまとめる
/// その結果をUIに渡すことで入力処理をUIに持たせず処理させることができる
/// </summary>
struct UIInput
{
public:
	bool key[static_cast<int>(UIInputState::Key::Max)][UIInputState::Max] = {
		{ false ,false ,false ,false },
		{ false ,false ,false ,false },
		{ false ,false ,false ,false },
		{ false ,false ,false ,false },
		{ false ,false ,false ,false },
		{ false ,false ,false ,false },
		{ false ,false ,false ,false },
	};
};
