#pragma once
#include<DxLib.h>
/// <summary>
/// シングルトンにしてどこからでも呼べるようにする
/// </summary>
class Time
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns></returns>
	static Time& GetInstance();
	~Time() = default;
	/// <summary>
	/// 現在の時間を更新
	/// </summary>
	void Update();
	/// <summary>
	/// 処理の待機
	/// </summary>
	void WaitProcess();

	/// <summary>
	/// 時間の速度を加味した経過時間の取得
	/// </summary>
	/// <returns></returns>
	float GetDeltaTime()const { return m_deltaTime * m_timeScale; }
	float GetLastTime()const { return m_LastTime; }
	/// <summary>
	/// 時間の速度を無視した経過時間の取得
	/// </summary>
	/// <returns></returns>
	float GetUnscaledDeltaTime()const { return m_deltaTime; }

	/// <summary>
	/// 時間の速度のゲッター・セッター
	/// </summary>
	/// <returns></returns>
	float GetTimeScale()const { return m_timeScale; }
	void SetTimeSacle(float timeScale) { m_timeScale = timeScale; }

	/// <summary>
	/// フレームレートのゲッター・セッター
	/// </summary>
	/// <returns></returns>
	int GetFrameRate() { return m_frameRate; }
	void SetFrameRate(int frameRate = 60) { m_frameRate = frameRate; }
private:
	/// <summary>
	/// シングルトンなのでprivateにして生成できないようにする
	/// </summary>
	Time();
	// コピー禁止
	Time(const Time&) = delete;
	// コピー代入を禁止
	Time& operator=(const Time&) = delete;
	// ムーブ禁止
	Time(Time&&) = delete;
	// ムーブ代入禁止
	Time& operator= (const Time&&) = delete;
private:
	/// <summary>
	/// 現在の時間
	/// </summary>
	LONGLONG m_LastTime;
	/// <summary>
	/// フレーム間の経過時間
	/// </summary>
	float m_deltaTime;
	/// <summary>
	/// 時間の速度(倍率)
	/// </summary>
	float m_timeScale;
	/// <summary>
	/// 1秒間のフレーム更新回数
	/// </summary>
	int m_frameRate;
};
