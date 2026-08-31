#include"GamePadState.h"
#include<math.h>
#include"Utility/MyMath.h"



GamePadState::GamePadState(const XINPUT_STATE& inputState) :
	m_rightThumb(InputThumb(inputState.ThumbRX, inputState.ThumbRY)),
	m_leftThumb(InputThumb(inputState.ThumbLX, inputState.ThumbLY)),
	m_rightTrigger(InputTrigger(inputState.RightTrigger)),
	m_leftTrigger(InputTrigger(inputState.LeftTrigger)),
	m_isKeyDown()
{
	// すべてfasleで初期化
	m_isKeyDown.fill(false);
	// 各ボタンの入力状況を取得
	for (int i = 0; i <= static_cast<int>(Input::GamePadKey::North); i++) {
		m_isKeyDown[i] = inputState.Buttons[i];
	}
	// スティックの入力方向をキャッシュ
	ThumbData leftThumbData = m_leftThumb.GetThumbData();
	ThumbData rightThumbData = m_rightThumb.GetThumbData();
	if(leftThumbData.tiltRatio>MyMath::Epsilon)
	// 左右スティックの4方向の入力を取得
	for (int i = 0; i < static_cast<int>(DirectionFour::Max); i++) {
		// スティック入力方向のキーIDを取得
		int thumbDirection = static_cast<int>(Input::GamePadKey::LeftThumbUp) + i;
		// 入力方向が一致しているとき
		if (leftThumbData.directionFour != static_cast<DirectionFour>(i))continue;
		// 入力がされている
		m_isKeyDown[thumbDirection] = true;
		break;
	}
	if(rightThumbData.tiltRatio>MyMath::Epsilon)
	for (int i = 0; i < static_cast<int>(DirectionFour::Max); i++) {
		// スティック入力方向のキーIDを取得
		int thumbDirection = static_cast<int>(Input::GamePadKey::RightThumbUp) + i;
		// 入力方向が一致しているとき
		if (rightThumbData.directionFour != static_cast<DirectionFour>(i))continue;
		// 入力がされている
		m_isKeyDown[thumbDirection] = true;
		break;
	}
}
