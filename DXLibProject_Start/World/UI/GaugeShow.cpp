#include "GaugeShow.h"
#include "Gauge.h"
#include<string>
#include<DxLib.h>
#include"../../Utility/MyMath.h"
namespace {
	// ファイルパス
	const char* const kFilePath = "Resource\\UI\\";
	const char* const kTypePath[static_cast<int>(GaugeType::Max)] = {
	 "HP",
	 "MP",
	};
	const char* const kGaugePath = "Gauge.png";
	const char* const kFramePath = "Frame.png";


	constexpr float kScale = 0.2f;
}

GaugeShow::GaugeShow() :
	m_gauge(nullptr),
	m_gaugeHandle(-1),
	m_frameHandle(-1),
	m_drawPos(Vector3::zero),
	m_rate(0)
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
	//DrawRotaGraph(m_drawPos.x, m_drawPos.y, 1, 0, m_gaugeHandle, TRUE);
	float lerp = m_gauge->GetRate() - m_rate;
	if (MyMath::Abs(lerp) < 0.001f)
		m_rate = m_gauge->GetRate();
	else {
	lerp *= 0.2f;
	m_rate += lerp;
	}
	float rate = 1 - m_rate;
	float posX = m_drawPos.x + sizeX * (rate-0.5f);
	float posY = m_drawPos.y - sizeY * 0.5f;
	DrawRectGraph(posX, posY, (sizeX * rate), 0, sizeX, sizeY, m_gaugeHandle, TRUE, FALSE);
	DrawCircle(posX, posY, 10, GetColor(255, 0, 0),TRUE);
}
