#pragma once
#include"../../System/ImageResource.h"
#include"Core/UIObject.h"
#include<memory>
namespace {
	// 顔背景の画像ID
	constexpr int kFaceBackGraphID = 2000;
	// ゲージ背景の画像ID
	constexpr int kGaugeBackGraphID = 2001;

}
class CharaGauge:public UIObject
{
public:
	CharaGauge()=default;
	~CharaGauge()=default;



protected:
	// キャラクターの顔画像
	std::shared_ptr<ImageResource> m_faceImage;
	// 顔画像の背景画像
	std::shared_ptr<ImageResource> m_faceBackImage;
	// ゲージの背景画像
	std::shared_ptr<ImageResource> m_backImage;
};

