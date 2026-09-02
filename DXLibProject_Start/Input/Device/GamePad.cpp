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
		Input::Key key = static_cast<Input::Key>(i);

		if (key == Input::Key::GpCross) {
			// 十字のいずれかが入力されていれば入力されている
			m_inputState.m_isKeyDown[i] = (
				IsDown(static_cast<int>(Input::Key::GpUp)) ||
				IsDown(static_cast<int>(Input::Key::GpRight)) ||
				IsDown(static_cast<int>(Input::Key::GpDown)) ||
				IsDown(static_cast<int>(Input::Key::GpLeft)));
		}
		if (key == Input::Key::GpRightVector) {
			// 右スティック4方向のいずれかが入力されていれば入力されている
			m_inputState.m_isKeyDown[i] = (
				IsDown(static_cast<int>(Input::Key::GpRightThumbUp)) ||
				IsDown(static_cast<int>(Input::Key::GpRightThumbRight)) ||
				IsDown(static_cast<int>(Input::Key::GpRightThumbDown)) ||
				IsDown(static_cast<int>(Input::Key::GpRightThumbLeft)));
		}
		if (key == Input::Key::GpLeftVector) {
			// 左スティック4方向のいずれかが入力されていれば入力されている
			m_inputState.m_isKeyDown[i] = (
				IsDown(static_cast<int>(Input::Key::GpLeftThumbUp)) ||
				IsDown(static_cast<int>(Input::Key::GpLeftThumbRight)) ||
				IsDown(static_cast<int>(Input::Key::GpLeftThumbDown)) ||
				IsDown(static_cast<int>(Input::Key::GpLeftThumbLeft)));
		}

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
	VectorState vectorState = GetVectorState(static_cast<int>(Input::GamePadKey::LeftThumb));
	printfDx("LeftThumb sqLength : %f\n", leftThumbData.vectorState.vector.GetSqLength());
	printfDx("LeftThumb tiltRatio : %f\n", leftThumbData.vectorState.ratio);
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

VectorState GamePad::GetVectorState(int deviceKeyID)
{
	Input::GamePadKey key = static_cast<Input::GamePadKey>(deviceKeyID);
	// 指定方向のスティックの入力ベクトルを返す
	if (key == Input::GamePadKey::RightThumb)return m_inputState.m_rightThumb.GetThumbData().vectorState;
	if (key == Input::GamePadKey::LeftThumb)return m_inputState.m_leftThumb.GetThumbData().vectorState;
	// 十字が指定されていたら十字の入力結果を返す
	if (key == Input::GamePadKey::Cross)return GetCrossVectorState();
	// どれでもない場合は未入力を返す
	return VectorState();
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
	case DirectionFour::Left:
		return "Left";
	case DirectionFour::Max:
	default:
		break;
	}
	return "";
}

VectorState GamePad::GetCrossVectorState()
{
	Vector2 input = Vector2::Zero;
	if (IsDown(static_cast<int>(Input::GamePadKey::Right)))input.x += 1.0f;
	if (IsDown(static_cast<int>(Input::GamePadKey::Left)))input.x -= 1.0f;
	if (IsDown(static_cast<int>(Input::GamePadKey::Up)))input.y += 1.0f;
	if (IsDown(static_cast<int>(Input::GamePadKey::Down)))input.y -= 1.0f;
	float radian = atan2(input.y, input.x);
	float ratio = (input.GetSqLength()) ? 1.0f : 0.0f;
	return { input,radian,ratio };
}

