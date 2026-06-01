#pragma once

/// <summary>
/// ウィンドウやゲームループに関するデータ
/// </summary>
namespace Game {

	// ウィンドウの名前
	const char* const kWindowText = "Test";

	// ウィンドウサイズ
	constexpr float kWindowScale =1.0f;
	constexpr int kScreenWidth = 1920 * kWindowScale;
	constexpr int kScreenHeight = 1080 * kWindowScale;

	// ウィンドウのカラーモード
	constexpr int kColorBit = 32;

	// FPS計測用の変数
	// 60FPSで動作させるので、1000000(マイクロ秒) / 60 (FPS)
	constexpr int kElapsedTime = 16667;

	// ウィンドウモード
	constexpr bool kWindowMode = true;

}



