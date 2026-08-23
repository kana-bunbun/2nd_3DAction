#pragma once
#include"Input/InputConst.h"
struct InputKeyParam {
public:
	/// <summary>
	/// 対応しているデバイス
	/// </summary>
	Input::Device device = Input::Device::Invalid;
	/// <summary>
	/// デバイス依存のキー番号
	/// </summary>
	int keyID=-1;
};