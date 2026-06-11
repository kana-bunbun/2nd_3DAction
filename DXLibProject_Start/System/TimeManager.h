#pragma once
#include<DxLib.h>
class TimeManager
{
public:

	static void Init();
	static void Update();
	/// <summary>
	/// 時間倍率を適応した経過時間を取得
	/// </summary>
	static float GetDeltaTime();
	/// <summary>
	/// 時間倍率が適応されていない経過時間を取得する
	/// </summary>
	static float GetRawDeltaTime();
	/// <summary>
	/// 時間倍率を取得
	/// </summary>
	static float GetTimeScale();
	/// <summary>
	/// 時間倍率を設定する
	/// </summary>
	static void SetTimeScale(float timeScale);
	/// <summary>
	/// 現在のFPSを取得
	/// </summary>
	static float GetFPS();

private:
	/// <summary>
	/// 前回計測した時間を格納する
	/// </summary>
	static LONGLONG m_prevTime;
	// 前回計測した時間と最新の計測した時間の差分 (時間倍率適応後)
	static float m_deltaTime;
	// 前回計測した時間と最新の計測した時間の差分 (時間倍率適応前)
	static float m_rawdeltaTime;
	// 時間倍率
	static float m_timeScale;
	// FPS用の計測した合計時間
	static float m_fpsTimer;
	// FPS用のフレームカウント
	static int m_flameCount;
	// 現在のFPS
	static float m_fps;
};

