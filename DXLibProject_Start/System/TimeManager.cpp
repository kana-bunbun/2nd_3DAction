#include "TimeManager.h"

#include<DxLib.h>
#include<cassert>

namespace {
	/// <summary>
	/// 1秒あたりのカウント数
	/// </summary>
	constexpr float kCountPerSecond = 1000000.0f;
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
int	TimeManager::m_flameCount=0;
float TimeManager::m_fps = 0.0f;

void TimeManager::Init()
{
	m_prevTime = 0;
	m_deltaTime = 0.0f;
	m_rawdeltaTime = 0.0f;
	m_timeScale = 1.0f;
	m_fpsTimer = 0.0f;
	m_flameCount = 0;
	m_fps = 0.0f;
}

void TimeManager::Update()
{

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
