#include "GaugeShow.h"
#include "Gauge.h"
#include<string>
#include<DxLib.h>
#include"../../Utility/MyMath.h"
#include"../../Utility/Time.h"
#include"GaugeParam.h"
namespace {
	// ファイルパス
	const char* const kFilePath = "Resource\\UI\\";
	const char* const kTypePath[static_cast<int>(GaugeType::Max)] = {
	 "HP",
	 "MP",
	};
	const char* const kGaugePath = "Gauge";
	const char* const kHeadPath = "Head.png";
	const char* const kBodyPath = "Body.png";
	const char* const kFramePath = "Frame.png";
	const char* const kFrontPath = "Front.png";


	constexpr float kGaugeLerp = 15.0f;


	
}

GaugeShow::GaugeShow() :
	m_gauge(nullptr),
	m_bodyHandle(-1),
	m_headHandle(-1),
	m_frameHandle(-1),
	m_frontHandle(-1),
	m_drawPos(Vector3::zero),
	m_rate(0)
{

}

GaugeShow::GaugeShow(Vector3 position,int type):
	m_gauge(nullptr),
	m_bodyHandle(-1),
	m_frameHandle(-1),
	m_frontHandle(-1),
	m_drawPos(position),
	m_rate(0)
{
	// ファイルパスを組み立てる
	std::string filePath;
	filePath = kFilePath;
	filePath += kTypePath[type];
	// ゲージの枠のグラフィックハンドルの読み込み
	m_frameHandle = LoadGraph((filePath + kFramePath).c_str());
	m_frontHandle = LoadGraph((filePath + kFrontPath).c_str());
	filePath += kGaugePath;
	// ゲージ本体のグラフィックハンドルの読み込み
	m_bodyHandle = LoadGraph((filePath + kBodyPath).c_str());
	m_headHandle = LoadGraph((filePath + kHeadPath).c_str());
	GetGraphSize(m_frameHandle, &m_graphSizeX, &m_graphSizeY);
}

GaugeShow::~GaugeShow()
{
	if (m_gauge) {
		m_gauge = nullptr;
		delete m_gauge;
	}
	DeleteGraph(m_bodyHandle);
	DeleteGraph(m_headHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_frontHandle);
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
	DrawRotaGraph(m_drawPos.x, m_drawPos.y, GaugeParam::kInitScale, 0, m_frameHandle, TRUE);

	//DrawRotaGraph(m_drawPos.x, m_drawPos.y, 1, 0, m_gaugeHandle, TRUE);
	float deltaTime = Time::GetInstance().GetDeltaTime();
	float lerp = m_gauge->GetRate() - m_rate;
	if (MyMath::Abs(lerp) < 0.001f)
		m_rate = m_gauge->GetRate();
	else {
		lerp *= MyMath::Clamp(kGaugeLerp * deltaTime,0.0f,1.0f);
	m_rate += lerp;
	}
	float rate = 1 - m_rate;
	int sizeX;
	int sizeY;
	GetGraphSize(m_bodyHandle, &sizeX, &sizeY);
	sizeX *= GaugeParam::kInitScale;
	sizeY *= GaugeParam::kInitScale;
	Vector3 pos1 = m_drawPos - Vector3(sizeX, sizeY, 0) * 0.5f;
	Vector3 pos2 = m_drawPos + Vector3(sizeX, sizeY, 0) * 0.5f;

	pos1.x += sizeX * rate;
	float addPosY = sizeY * 0.5f;
	//DrawRectGraph(posX, posY, (m_graphSizeX * rate), 0, m_graphSizeX, m_graphSizeY, m_bodyHandle, TRUE, FALSE);
	DrawExtendGraph(pos1.x, pos1.y, pos2.x, pos2.y, m_bodyHandle, TRUE);
	DrawRotaGraph(pos1.x, pos1.y+addPosY, GaugeParam::kInitScale, 0, m_headHandle, TRUE);
	DrawRotaGraph(pos2.x, m_drawPos.y, GaugeParam::kInitScale, 0, m_frontHandle, TRUE);


}
