#pragma once
#include"pch.h"

#include"Input/InputData.h"
#include<unordered_map>
#include"Utility/UIInputKey.h"
/// <summary>
/// Sceneで入力した結果を構造体にまとめる
/// その結果をUIに渡すことで入力処理をUIに持たせず処理させることができる
/// </summary>

class UIInput
{
public:
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
	UIInputKey keys[static_cast<int>(UIInput::Key::Max)];
	bool IsDown(const UIInput::Key& key) { return keys[static_cast<int>(key)].IsDown(); }
	bool IsPressed(const UIInput::Key& key) { return keys[static_cast<int>(key)].IsPressed(); }
	bool IsReleased(const UIInput::Key& key) { return keys[static_cast<int>(key)].IsReleased(); }
public:
};

