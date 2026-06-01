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
	Vector3 GetPosition() { return m_drawPos; }
	Vector3 GetGaugeSize() { return Vector3(m_graphSizeX, m_graphSizeY, 0.0f); }
private:
	Gauge* m_gauge;
	int m_bodyHandle;
	int m_headHandle;
	int m_frameHandle;
	int m_frontHandle;
	Vector3 m_drawPos;
	int m_graphSizeX;
	int m_graphSizeY;
	float m_rate;
};

