#include "GamePad.h"
#include<DxLib.h>
#include<math.h>
#include<cassert>
#include"Input/InputConst.h"
#include"Utility/MyMath.h"
#include"Input/Device/GamePad/GamePadState.h"
GamePad::GamePad(int padID):
m_padID(padID),
m_inputState(XINPUT_STATE())
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
	for (int i = 0; i < m_inputState.isKeyDown.size(); i++) {
		// 長押し時間を更新
		m_holdTime[0][i] += deltaTime;

		if (m_inputState.isKeyDown[i])continue;
		// 入力していなければ長押し時間を0に
		m_holdTime[0][i] = 0;
	}
}

bool GamePad::IsDown(int deviceKeyID)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return m_inputState.isKeyDown[deviceKeyID];
}

bool GamePad::IsPressed(int deviceKeyID)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0 || deviceKeyID >= static_cast<int>(Input::GamePadKey::Max)) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return (m_holdTime[0][deviceKeyID] && !m_holdTime[1][deviceKeyID]);
}

bool GamePad::IsReleased(int deviceKeyID)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return (!m_holdTime[0][deviceKeyID] && m_holdTime[1][deviceKeyID]);
}

bool GamePad::IsHold(int deviceKeyID, int holdCount)
{
	// 不正値ならfalseを返す
	if (deviceKeyID < 0) {
		assert(false && "不正なキーの入力チェックが行われました");
		return false;
	}
	// 指定キーの入力状態を返す
	return m_holdTime[0][deviceKeyID] >= holdCount;
}

Vector2 GamePad::GetVector(const Input::DirectionHolizontal& direction)
{
	// 指定方向のスティックの入力ベクトルを返す
	if (direction == Input::DirectionHolizontal::Right)return m_inputState.rightThumb.tilt;
	if (direction == Input::DirectionHolizontal::Left)return m_inputState.leftThumb.tilt;
	// 左右どちらでもない場合は未入力を返す
	return Vector2::Zero;
}

