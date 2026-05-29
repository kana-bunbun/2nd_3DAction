#pragma once
#include"../../Utility/Vector3.h"
class Gauge;

namespace {
	enum GaugeType {
		HP,
		MP,
		Max
	};
}

class GaugeShow
{
public:
	GaugeShow();
	GaugeShow(Vector3 position,int type);
	~GaugeShow();
	void Init();
	void End();
	void Update();
	void Draw();

public:		// ゲッター・セッター
	void SetGauge(Gauge* gauge) { m_gauge = gauge; }
	void SetPosition(const Vector3& position) { m_drawPos = position; }
private:
	Gauge* m_gauge;
	int m_gaugeHandle;
	int m_frameHandle;
	Vector3 m_drawPos;
};

