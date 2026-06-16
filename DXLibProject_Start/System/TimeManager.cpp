#include "TimeManager.h"

#include<DxLib.h>
#include<cassert>

namespace {
	/// <summary>
	/// 1秒あたりのカウント数
	/// </summary>
	constexpr float kCountPerSecond = 0.000001f;
	/// <summary>
	/// 最大のdeltaTime 0.1f = 100ms
	/// ブレイクポイントやウィンドウがアクティブになっていないときの応急処置
	/// </summary>
	constexpr float kMaxDeltaTime = 0.1f;

}

// 静的メンバ変数の初期化
LONGLONG TimeManager::m_prevTime=0;
float TimeManager::m_deltaTime=0.0f;
float TimeManager::m_rawdeltaTime=0.0f;
float TimeManager::m_timeScale = 1.0f;
float TimeManager::m_fpsTimer = 0.0f;
int	TimeManager::m_frameCount=0;
float TimeManager::m_fps = 0.0f;

void TimeManager::Init()
{
	m_prevTime = GetNowHiPerformanceCount();
	m_deltaTime = 0.0f;
	m_rawdeltaTime = 0.0f;
	m_timeScale = 1.0f;
	m_fpsTimer = 0.0f;
	m_frameCount = 0;
	m_fps = 0.0f;
}

/// <summary>
/// 経過時間の計測
/// デバッグ確認用の異常値対応
/// 時間倍率適応
/// FPS計測
/// </summary>
void TimeManager::Update()
{
	// 現在の時間を計算
	LONGLONG currentTime = GetNowHiPerformanceCount();
	// 経過時間を計算
	LONGLONG differ = currentTime - m_prevTime;
	// 経過時間を1秒に変換
	float deltaTime = differ * kCountPerSecond;
	// デバッグ等の確認環境による異常値を制限
	if (deltaTime > kMaxDeltaTime)
		deltaTime = kMaxDeltaTime;
	// 時間倍率適応前に更新
	m_rawdeltaTime = deltaTime;
	m_deltaTime = deltaTime* m_timeScale;

	// FPSを計算
	m_fpsTimer += m_rawdeltaTime;
	m_frameCount++;
	if (m_fpsTimer >= 1.0f) {
		// 1秒経過したらFPSを出す
		m_fps = static_cast<float>(m_frameCount);
		// リセット
		m_frameCount = 0;
		m_fpsTimer = 0.0f;
	}
	m_prevTime = currentTime;

}

float TimeManager::GetDeltaTime()
{
	return m_deltaTime;

}


float TimeManager::GetRawDeltaTime()
{
	return m_rawdeltaTime;

}

float TimeManager::GetTimeScale()
{
	return m_timeScale;

}

void TimeManager::SetTimeScale(float timeScale)
{
	if (timeScale < 0.0f) {
		assert(0 && "TimeManager:SetTimeScale : m_timeScale < 0.0f");
		timeScale = 0.0f;
	}
	m_timeScale = timeScale;
}

float TimeManager::GetFPS()
{
	return m_fps;
}
