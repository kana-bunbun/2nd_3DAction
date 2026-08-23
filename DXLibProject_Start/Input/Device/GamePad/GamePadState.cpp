#include"GamePadState.h"
#include<math.h>
#include"Utility/MyMath.h"



GamePadState::GamePadState(const XINPUT_STATE& inputState) :
	rightThumb(InputThumb(inputState.ThumbRX, inputState.ThumbRY)),
	leftThumb(InputThumb(inputState.ThumbLX, inputState.ThumbLY)),
	rightTrigger(InputTrigger(inputState.RightTrigger)),
	leftTrigger(InputTrigger(inputState.LeftTrigger)),
	isKeyDown()
{
	// すべてfasleで初期化
	isKeyDown.fill(false);
	// 各ボタンの入力状況を取得
	for (int i = 0; i <= static_cast<int>(Input::GamePadKey::North); i++) {
		isKeyDown[i] = inputState.Buttons[i];
	}
	// 左右スティックの4方向の入力を取得
	for (int i = 0; i < static_cast<int>(Input::DirectionFour::Max); i++) {
		int thumbDirection = static_cast<int>(Input::GamePadKey::LeftThumbUp) + i;
		isKeyDown[thumbDirection] = (leftThumb.directionFour == static_cast<Input::DirectionFour>(i));
		if (isKeyDown[thumbDirection])break;
	}
	for (int i = 0; i < static_cast<int>(Input::DirectionFour::Max); i++) {
		int thumbDirection = static_cast<int>(Input::GamePadKey::RightThumbUp) + i;
		isKeyDown[thumbDirection] = (rightThumb.directionFour == static_cast<Input::DirectionFour>(i));
		if (isKeyDown[thumbDirection])break;
	}
}
