#include"pch.h"
#include "MPShow.h"
#include"../../System/ImageManager.h"
namespace {
	// MPゲージの端の画像のパスID
	constexpr int kHeadGraphID = 2020;
	// MPゲージの真ん中の画像のパスID
	constexpr int kBodyGraphID = 2021;
	// MPゲージの装飾の画像のパスID
	constexpr int kFrontGraphID = 2022;
	// MPゲージの枠画像のパスID
	constexpr int kFrameGraphID = 2023;

}
MPShow::MPShow(const Vector3& position)
{
	// ゲージ本体のグラフィックハンドルの読み込み
	m_headImage = ImageManager::GetInstance().GetImage(kHeadGraphID);
	m_bodyImage = ImageManager::GetInstance().GetImage(kBodyGraphID);
	// ゲージの枠のグラフィックハンドルの読み込み
	m_frontImage = ImageManager::GetInstance().GetImage(kFrontGraphID);
	m_frameImage = ImageManager::GetInstance().GetImage(kFrameGraphID);
	GetGraphSize(m_frameImage->GetHandle(), &m_graphSizeX, &m_graphSizeY);
}

MPShow::~MPShow()
{}
