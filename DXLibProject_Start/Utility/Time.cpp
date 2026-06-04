#include "Time.h"
#include<DxLib.h>
namespace {
	constexpr float kMicroSecond = 0.000001f;
}

Time::Time()
{
	m_deltaTime = 0;
	m_LastTime = GetNowHiPerformanceCount();
	m_timeScale = 1;
	m_frameRate = 60;
}

Time& Time::GetInstance()
{
	static Time instance;
	return instance;
}

void Time::Update()
{
	m_deltaTime = (GetNowHiPerformanceCount() - m_LastTime) * kMicroSecond;
	m_LastTime = GetNowHiPerformanceCount();

	//WaitProcess();
	if (m_deltaTime > 0.5f)
		m_deltaTime = 0.5f;
}

void Time::WaitProcess()
{
	// 割り算を使うためm_frameRateが0なら処理しない
	if (!m_frameRate)return;
	float frameRate = 1.0f / m_frameRate;

	// フレームレート維持のため待機
	m_deltaTime = (GetNowHiPerformanceCount() - m_LastTime) * kMicroSecond;
	while (m_deltaTime<frameRate)
	{

		m_deltaTime = (GetNowHiPerformanceCount() - m_LastTime)*kMicroSecond;
	}
}


