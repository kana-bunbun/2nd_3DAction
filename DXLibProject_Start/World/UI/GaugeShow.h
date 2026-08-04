#pragma once
#include"../../Utility/Vector3.h"
#include"../../System/ImageResource.h"
#include<memory>
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
	GaugeShow(const Vector3& position);
	~GaugeShow();
	virtual void Init();
	virtual void End();
	virtual void Update(float deltaTime);
	virtual void Draw();

public:		// ゲッター・セッター
	void SetPosition(const Vector3& position) { m_drawPos = position; }
	Vector3 GetPosition() { return m_drawPos; }
	const Vector3& GetGaugeSize() { return Vector3(m_graphSizeX, m_graphSizeY, 0.0f); }
protected:
	float m_targetRate;
	std::shared_ptr<ImageResource> m_bodyImage;
	std::shared_ptr<ImageResource> m_headImage;
	std::shared_ptr<ImageResource> m_frameImage;
	std::shared_ptr<ImageResource> m_frontImage;
	Vector3 m_drawPos;
	int m_graphSizeX;
	int m_graphSizeY;
	float m_rate;
};

