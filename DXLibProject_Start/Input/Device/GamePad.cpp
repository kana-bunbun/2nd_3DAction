#include "GamePad.h"
#include<DxLib.h>
#include<cassert>
#include"Input/InputConst.h"
#include"Input/Device/GamePad/GamePadState.h"
GamePad::GamePad(int padID):
m_padID(padID),
m_inputState(XINPUT_STATE()),
m_holdTime()
{
}
void GamePad::Init()
{}
void GamePad::Update(float deltaTime)
{
	// このtローラーの入力情報を取得
	XINPUT_STATE inputState;
	GetJoypadXInputState(m_padID, &inputState);
	m_inputState = GamePadState(inputState);

	// 長押し時間の更新
	m_holdTime[1] = m_holdTime[0];
	// すべてのキーを調べる
	for (int i = 0; i < m_inputState.m_isKeyDown.size(); i++) {
		// 長押し時間を更新
		m_holdTime[0][i] += deltaTime;

		if (m_inputState.m_isKeyDown[i])continue;
		// 入力していなければ長押し時間を0に
		m_holdTime[0][i] = 0;
	}
	ThumbData leftThumbData = m_inputState.m_leftThumb.GetThumbData();
	ThumbData rightThumbData = m_inputState.m_rightThumb.GetThumbData();
	printfDx("LeftTumb dir : %s\n",GetDirectionText(leftThumbData.directionFour).c_str());
	printfDx("LeftTumb dir : %d\n", leftThumbData.directionFour);
	printfDx("RightTumb dir : %s\n", GetDirectionText(rightThumbData.directionFour).c_str());
	printfDx("RightTumb dir : %d\n",rightThumbData.directionFour);
	printfDx("LeftThumb sqLength : %f\n", leftThumbData.tilt.GetSqLength());
	printfDx("LeftThumb tiltRatio : %f\n", leftThumbData.tiltRatio);
}

bool GamePad::IsDown(int deviceKeyID)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	bool down= m_inputState.m_isKeyDown[deviceKeyID] > MyMath::Epsilon;
	// 指定キーの入力状態を返す
	return down;
}

bool GamePad::IsPressed(int deviceKeyID)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0 || deviceKeyID >= static_cast<int>(Input::GamePadKey::Max)) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	bool pressed = (m_holdTime[0][deviceKeyID] > MyMath::Epsilon && m_holdTime[1][deviceKeyID] < MyMath::Epsilon);
	return pressed;
}

bool GamePad::IsReleased(int deviceKeyID)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	bool released = (m_holdTime[0][deviceKeyID]<MyMath::Epsilon && m_holdTime[1][deviceKeyID] > MyMath::Epsilon);
	return released;
}

bool GamePad::IsHold(int deviceKeyID, int holdCount)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	bool hold = (m_holdTime[0][deviceKeyID] >= holdCount);
	return hold;
}

Vector2 GamePad::GetVector(const Input::DirectionHolizontal& direction)
{
	// 指定方向のスティックの入力ベクトルを返す
	if (direction == Input::DirectionHolizontal::Right)return m_inputState.m_rightThumb.GetThumbData().tilt;
	if (direction == Input::DirectionHolizontal::Left)return m_inputState.m_leftThumb.GetThumbData().tilt;
	// 左右どちらでもない場合は未入力を返す
	return Vector2::Zero;
}

std::string GamePad::GetDirectionText(DirectionFour direction)
{
	switch (direction)
	{
	case DirectionFour::Invalid:
		return "Invalid";
	case DirectionFour::Up:
		return "Up";
	case DirectionFour::Right:
		return "Right";
	case DirectionFour::Down:
		return "Down";
	case DirectionFour::left:
		return "Left";
	case DirectionFour::Max:
	default:
		break;
	}
	return "";
}

