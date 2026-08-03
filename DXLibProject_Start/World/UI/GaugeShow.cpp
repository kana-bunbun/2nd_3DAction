#include "GaugeShow.h"
#include<string>
#include<DxLib.h>
#include"../../Utility/MyMath.h"
#include"GaugeParam.h"
#include"../../System/ImageManager.h"
namespace {



	constexpr float kGaugeLerp = 15.0f;
}

GaugeShow::GaugeShow() :
	//m_gauge(nullptr),
	m_bodyImage(nullptr),
	m_headImage(nullptr),
	m_frameImage(nullptr),
	m_frontImage(nullptr),
	m_drawPos(Vector3::zero),
	m_rate(0)
{

}

GaugeShow::GaugeShow(const Vector3& position):
	m_bodyImage(nullptr),
	m_frameImage(nullptr),
	m_frontImage(nullptr),
	m_drawPos(position),
	m_rate(0)
{
	// ゲージの枠のグラフィックハンドルの読み込み
	m_frameImage = ImageManager::GetInstance().GetImage(0);
	m_frontImage = ImageManager::GetInstance().GetImage(0);
	// ゲージ本体のグラフィックハンドルの読み込み
	m_bodyImage = ImageManager::GetInstance().GetImage(0);
	m_headImage = ImageManager::GetInstance().GetImage(0);
	GetGraphSize(m_frameImage->GetHandle(), &m_graphSizeX, &m_graphSizeY);
}

GaugeShow::~GaugeShow()
{
}

void GaugeShow::Init()
{

}

void GaugeShow::End()
{

}

void GaugeShow::Update(float deltaTime)
{
	////DrawRotaGraph(m_drawPos.x, m_drawPos.y, 1, 0, m_gaugeHandle, TRUE);
	//float lerp = m_targetRate - m_rate;
	////if (MyMath::Abs(lerp) < 0.001f)
	////	m_rate = m_gauge->GetRate();
	//else {
	//	lerp *= MyMath::Clamp(kGaugeLerp * deltaTime,0.0f,1.0f);
	//m_rate += lerp;
	//}
}

void GaugeShow::Draw()
{
	DrawRotaGraph(m_drawPos.x, m_drawPos.y, GaugeParam::kPlayerGaugeScale, 0, m_frameImage->GetHandle(), TRUE);


	float rate = 1 - m_rate;
	int sizeX;
	int sizeY;
	GetGraphSize(m_bodyImage->GetHandle(), &sizeX, &sizeY);
	sizeX *= GaugeParam::kPlayerGaugeScale;
	sizeY *= GaugeParam::kPlayerGaugeScale;
	Vector3 pos1 = m_drawPos - Vector3(sizeX, sizeY, 0) * 0.5f;
	Vector3 pos2 = m_drawPos + Vector3(sizeX, sizeY, 0) * 0.5f;

	pos1.x += sizeX * rate;
	float addPosY = sizeY * 0.5f;
	//DrawRectGraph(posX, posY, (m_graphSizeX * rate), 0, m_graphSizeX, m_graphSizeY, m_bodyHandle, TRUE, FALSE);
	DrawExtendGraph(pos1.x, pos1.y, pos2.x, pos2.y, m_bodyImage->GetHandle(), TRUE);
	DrawRotaGraph(pos1.x, pos1.y+addPosY, GaugeParam::kPlayerGaugeScale, 0, m_headImage->GetHandle(), TRUE);
	DrawRotaGraph(pos2.x, m_drawPos.y, GaugeParam::kPlayerGaugeScale, 0, m_frontImage->GetHandle(), TRUE);


}
