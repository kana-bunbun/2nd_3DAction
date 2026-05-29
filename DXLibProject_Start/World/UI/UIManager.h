#pragma once
#include<memory>
#include<vector>
#include"GaugeShow.h"


class UIManager
{
public:
	UIManager();
	~UIManager();
	void Init();
	void End();
	void Update();
	void Draw();
	void AddGauge(const Vector3& position, int type, Gauge* gauge);
private:
	// ゲージの配列
	std::vector<std::unique_ptr<GaugeShow>> m_gaugeShow;
};

