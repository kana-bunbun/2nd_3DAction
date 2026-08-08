#pragma once
#include"../Utility/Vector3.h"
#include"../World/UI/Core/UIInput.h"

/// <summary>
/// 入力情報の取得・更新をする
/// </summary>

// 名前空間
namespace Input {

	enum class Pad {
		Invalid=-1,
		P1, // プレイヤー1
		P2, // プレイヤー2
		P3, // プレイヤー3
		P4, // プレイヤー4
		Max
	};
	
	//// 使用するボタン
	enum class Key {	
		B = XINPUT_BUTTON_B,				// Bボタン
		A = XINPUT_BUTTON_A,				// Aボタン
		Y = XINPUT_BUTTON_Y,				// Yボタン
		X = XINPUT_BUTTON_X,				// Xボタン
		RB= XINPUT_BUTTON_RIGHT_SHOULDER,	// RB
		LB= XINPUT_BUTTON_LEFT_SHOULDER,	// LB
		RT = 10,							// 右トリガー
		LT = 11,							// 左トリガー
		Up = XINPUT_BUTTON_DPAD_UP,			// 十字上
		Down = XINPUT_BUTTON_DPAD_DOWN,		// 十字下
		Right = XINPUT_BUTTON_DPAD_RIGHT,	// 十字右
		Left = XINPUT_BUTTON_DPAD_LEFT,		// 十字左
		Start=XINPUT_BUTTON_START,			// STARTボタン		
		Back=XINPUT_BUTTON_BACK,			// BACKボタン
		RThumb=XINPUT_BUTTON_RIGHT_THUMB,	// 右スティック押し込み
		LThumb=XINPUT_BUTTON_LEFT_THUMB,	// 左スティック押し込み
	};
	enum class Joystick {
		Right,								// 右スティック
		Left,								// 左スティック
		Max
	};

	void Init();

	/// 入力情報の取得・更新
	/// ゲームループで呼ぶ
	void Update();

	/// <summary>
	/// キーが押されているかどうかを調べる
	/// </summary>
	/// <param name="key">入力されたキー</param>
	/// <returns>入力結果 押されていたらtrue</returns>
	bool IsDown(Input::Key key, const Pad padNum);

	/// <summary>
	/// キーが押されているかどうかを調べる
	/// </summary>
	/// <param name="key">入力されたキー</param>
	/// <returns>入力結果 押された瞬間だったらtrue</returns>
	bool IsPressed(Input::Key key, const Pad padNum);

	/// <summary>
	/// キーが押されているかどうかを調べる
	/// </summary>
	/// <param name="key">入力されたキー</param>
	/// <returns>入力結果 離された瞬間だったらtrue</returns>
	bool IsReleased(Input::Key key, const Pad padNum);

	/// <summary>
	/// キーが長押しされているかどうか調べる
	/// </summary>
	/// <param name="key">入力されたキー</param>
	/// <returns>入力結果 長押しされていたらtrue</returns>
	constexpr float kHoldCount = 0.3f;
	bool IsHold(Input::Key key, const Pad padNum,float holdCount=kHoldCount);

	/// <summary>
	/// アナログレバーの入力角度を調べる
	/// </summary>
	/// <returns>入力角度のデグリー角</returns>
	float AnalogAngle(const Input::Joystick stick, const Pad padNum);
	/// <summary>
	/// アナログレバーの入力量を調べる
	/// </summary>
	/// <returns>レバーをどれだけ倒しているか,0～1</returns>
	float PadAnalogAmount(const Input::Joystick stick, const Pad padNum);

	/// <summary>
	/// デバッグ処理
	/// </summary>
	void Debug();

}

