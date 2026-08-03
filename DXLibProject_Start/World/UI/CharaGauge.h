#pragma once
#include"../../System/ImageResource.h"
#include<memory>
namespace {
	// 顔背景の画像ID
	constexpr int kFaceBackGraphID = 2000;
	// ゲージ背景の画像ID
	constexpr int kGaugeBackGraphID = 2001;

}
class CharaGauge
{
public:
	CharaGauge()=default;
	~CharaGauge()=default;

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	// キャラクターの顔画像
	std::shared_ptr<ImageResource> m_faceImage;
	// 顔画像の背景画像
	std::shared_ptr<ImageResource> m_faceBackImage;
	// ゲージの背景画像
	std::shared_ptr<ImageResource> m_backImage;
};

