#pragma once
#include<DxLib.h>
#include<array>
#include"Input/InputConst.h"
#include"Utility/Vector2.h"
#include"Input/Device/GamePad/InputThumb.h"
#include"Input/Device/GamePad/InputTrigger.h"
class GamePadState {
public:
	GamePadState(const XINPUT_STATE& inputState = XINPUT_STATE());
	InputThumb leftThumb;
	InputThumb rightThumb;
	InputTrigger rightTrigger;
	InputTrigger leftTrigger;
	std::array<bool, static_cast<int>(Input::GamePadKey::Max)> isKeyDown;
};