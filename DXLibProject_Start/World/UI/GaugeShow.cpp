#include "GaugeShow.h"
#include "Gauge.h"
#include<string>
#include<DxLib.h>
namespace {
	const char* const kFilePath = "Resource\\UI\\";
	const char* const kTypePath[static_cast<int>(GaugeType::Max)] = {
	 "HP",
	 "MP",
	};
	const char* const kGaugePath = "Gauge.png";
	const char* const kFramePath = "Frame.png";
}

GaugeShow::GaugeShow() :
	m_gauge(nullptr),
	m_gaugeHandle(-1),
	m_frameHandle(-1),
	m_drawPos(Vector3::zero)
{

}

GaugeShow::GaugeShow(Vector3 position,int type):
	m_gauge(nullptr),
	m_gaugeHandle(-1),
	m_frameHandle(-1),
	m_drawPos(position)
{
	// ファイルパスを組み立てる
	std::string filePath;
	filePath = kFilePath;
	filePath += kTypePath[type];
	// ゲージ本体のグラフィックハンドルの読み込み
	m_gaugeHandle = LoadGraph((filePath + kGaugePath).c_str());
	// ゲージの枠のグラフィックハンドルの読み込み
	m_frameHandle = LoadGraph((filePath + kFramePath).c_str());
}

GaugeShow::~GaugeShow()
{
	if (m_gauge) {
		m_gauge = nullptr;
		delete m_gauge;
	}
}

void GaugeShow::Init()
{

}

void GaugeShow::End()
{

}

void GaugeShow::Update()
{

}

void GaugeShow::Draw()
{
	DrawRotaGraph(m_drawPos.x, m_drawPos.y, 1, 0, m_frameHandle, TRUE);
	int sizeX = -1;
	int sizeY = -1;
	GetGraphSize(m_gaugeHandle, &sizeX, &sizeY);
	DrawRectGraph(m_drawPos.x, m_drawPos.y - 100, m_drawPos.x - (sizeX * 0.5f), m_drawPos.y - 100 - (sizeY * 0.5f), sizeX*m_gauge->GetRate(), sizeY, m_gaugeHandle, TRUE, FALSE);
	DrawRotaGraph(m_drawPos.x, m_drawPos.y, 1, 0, m_gaugeHandle, TRUE);
}
