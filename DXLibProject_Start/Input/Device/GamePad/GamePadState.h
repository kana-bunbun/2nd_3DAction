#pragma once
#include<DxLib.h>
#include<array>
#include"Input/InputConst.h"
#include"Input/Device/GamePad/InputThumb.h"
#include"Input/Device/GamePad/InputTrigger.h"
class GamePadState {
public:
	GamePadState(const XINPUT_STATE& inputState = XINPUT_STATE());
	InputThumb GetRightThumb() { return m_rightThumb; }
	InputThumb GetLeftThumb() { return m_leftThumb; }
	std::array<bool, static_cast<int>(Input::GamePadKey::Max)> m_isKeyDown;

private:
	InputThumb m_leftThumb;
	InputThumb m_rightThumb;
	InputTrigger m_rightTrigger;
	InputTrigger m_leftTrigger;
};