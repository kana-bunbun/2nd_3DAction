#include "GamePad.h"
#include<DxLib.h>
#include<math.h>
#include<cassert>
#include"Input/InputConst.h"
#include"Utility/MyMath.h"
namespace{
	// トリガーの最大入力値
	constexpr int kTriggerInputMax = 255;
	// スティックの最大入力値
	constexpr int kThumbInputMax = 32767;

	// 角度計算用の定数
	constexpr float kDirectonFourCalculateValue = 45.0f * MyMath::ToRadian;
	constexpr float kDirectonEightCalculateValue = kDirectonFourCalculateValue *0.5f;

}
GamePad::GamePad(int padID):
m_padID(padID),
m_inputState(XINPUT_STATE())
{
}
void GamePad::Update(float deltaTime)
{
	// このtローラーの入力情報を取得
	XINPUT_STATE inputState;
	GetJoypadXInputState(m_padID, &inputState);
	m_inputState = GamePadState(inputState);

	// 長押し時間の更新
	m_holdTime[1] = m_holdTime[0];
	// すべてのキーを調べる
	for (int i = 0; i < m_inputState.isKeyDown.size(); i++) {
		// 長押し時間を更新
		m_holdTime[0][i] += deltaTime;

		if (m_inputState.isKeyDown[i])continue;
		// 入力していなければ長押し時間を0に
		m_holdTime[0][i] = 0;
	}
}
int GamePad::GetKeyCode(const Input::Key& key)
{
	switch (key) {
	case Input::Key::GpUp:
		return Input::GamePadKey::Up;
	case Input::Key::GpRight:
		return Input::GamePadKey::Right;
	case Input::Key::GpDown:
		return Input::GamePadKey::Down;
	case Input::Key::GpLeft:
		return Input::GamePadKey::Left;
	case Input::Key::GpNorth:
		return Input::GamePadKey::North;
	case Input::Key::GpEast:
		return Input::GamePadKey::East;
	case Input::Key::GpSouth:
		return Input::GamePadKey::South;
	case Input::Key::GpWest:
		return Input::GamePadKey::West;
	case Input::Key::GpStart:
		return Input::GamePadKey::Start;
	case Input::Key::GpBack:
		return Input::GamePadKey::Back;
	case Input::Key::GpLeftShoulder:
		return Input::GamePadKey::LeftShoulder;
	case Input::Key::GpRightShoulder:
		return Input::GamePadKey::RightShoulder;
	case Input::Key::GpLeftTrigger:
		return Input::GamePadKey::LeftTrigger;
	case Input::Key::GpRightTrigger:
		return Input::GamePadKey::RightTrigger;
	case Input::Key::GpLeftThumb:
		return Input::GamePadKey::LeftThumb;
	case Input::Key::GpRightThumb:
		return Input::GamePadKey::RightThumb;
	case Input::Key::GpRightThumbUp:
		return Input::GamePadKey::RightThumbUp;
	case Input::Key::GpRightThumbRight:
		return Input::GamePadKey::RightThumbRight;
	case Input::Key::GpRightThumbDown:
		return Input::GamePadKey::RightThumbDown;
	case Input::Key::GpRightThumbLeft:
		return Input::GamePadKey::RightThumbLeft;
	case Input::Key::GpLeftThumbUp:
		return Input::GamePadKey::LeftThumbUp;
	case Input::Key::GpLeftThumbRight:
		return Input::GamePadKey::LeftThumbRight;
	case Input::Key::GpLeftThumbDown:
		return Input::GamePadKey::LeftThumbDown;
	case Input::Key::GpLeftThumbLeft:
		return Input::GamePadKey::LeftThumbLeft;
	}
	return Input::GamePadKey::Invalid;
}

bool GamePad::IsDown(const Input::Key& key)
{
	// キーをゲームパッド用に変換
	int keyID = GetKeyCode(key);
	// 不正値ならfalseを返す
	if (keyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return m_inputState.isKeyDown[keyID];
}

bool GamePad::IsPressed(const Input::Key& key)
{
	// キーをゲームパッド用に変換
	int keyID = GetKeyCode(key);
	// 不正値ならfalseを返す
	if (keyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return (m_holdTime[0][keyID] && !m_holdTime[1][keyID]);
}

bool GamePad::IsReleased(const Input::Key& key)
{
	// キーをゲームパッド用に変換
	int keyID = GetKeyCode(key);
	// 不正値ならfalseを返す
	if (keyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return (!m_holdTime[0][keyID] && m_holdTime[1][keyID]);
}

bool GamePad::IsHold(const Input::Key& key, int holdCount)
{
	// キーをゲームパッド用に変換
	int keyID = GetKeyCode(key);
	// 不正値ならfalseを返す
	if (keyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return m_holdTime[0][keyID] >= holdCount;
}

InputThumb::InputThumb(int holizontal, int vertical):
	tilt(Vector2::Zero),
	tiltRadian(0.0f),
	tiltRatio(0.0f)
{
	if (holizontal)
	{
		// 水平方向の入力があれば入力割合を取得
		tilt.x = MyMath::Clamp(static_cast<float>(holizontal / kThumbInputMax),-1.0f,1.0f);
	}
	if (vertical)
	{
		// 垂直方向の入力があれば入力割合を取得
		tilt.y = MyMath::Clamp(static_cast<float>(vertical / kThumbInputMax), -1.0f, 1.0f);
	}
	// 入力角度を求める
	tiltRadian = atan2(tilt.y, tilt.x);
	// 4方向の入力方向を取得
	int direction = static_cast<int>((tiltRadian - kDirectonFourCalculateValue) / (kDirectonFourCalculateValue * 2));
	directionFour = static_cast<Input::DirectionFour>(direction);
	// 8方向の入力方向を取得
	direction = static_cast<int>((tiltRadian - kDirectonEightCalculateValue) / (kDirectonEightCalculateValue * 2));
	directionEight = static_cast<Input::DirectionEight>(direction);
	if (!tilt.x && !tilt.y)return;
	// 入力があれば入力量を計算
	tiltRatio = tilt.GetLength() / static_cast<float>(kThumbInputMax);
}

InputTrigger::InputTrigger(int input)
{
	// 入力量を計算
	inputRatio = static_cast<float>(input / kTriggerInputMax);
}

GamePadState::GamePadState(const XINPUT_STATE& inputState):
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
