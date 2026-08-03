#include "HPShow.h"
#include"../../System/ImageManager.h"
namespace {
	// HPゲージの端の画像ID
	constexpr int kHeadGraphID = 2010;
	// HPゲージの真ん中の画像ID
	constexpr int kBodyGraphID = 2011;
	// HPゲージの装飾の画像ID
	constexpr int kFrontGraphID = 2012;
	// HPゲージの枠の画像ID
	constexpr int kFrameGraphID = 2013;
}
HPShow::HPShow(const Vector3& position)
{
	// ゲージ本体のグラフィックハンドルの読み込み
	m_headImage = ImageManager::GetInstance().GetImage(kHeadGraphID);
	m_bodyImage = ImageManager::GetInstance().GetImage(kBodyGraphID);
	// ゲージの枠のグラフィックハンドルの読み込み
	m_frontImage = ImageManager::GetInstance().GetImage(kFrontGraphID);
	m_frameImage = ImageManager::GetInstance().GetImage(kFrameGraphID);
	GetGraphSize(m_frameImage->GetHandle(), &m_graphSizeX, &m_graphSizeY);
}

HPShow::~HPShow()
{}
