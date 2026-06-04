#include "GaugeDragon.h"
#include "GaugeParam.h"
#include<string>
#include<DxLib.h>

#include"../Character/Guardian/Dragon.h"
#include"../../Utility/Vector3.h"

GaugeDragon::GaugeDragon() :
	m_gauge()
{
	std::string filePath = GaugeParam::kFilePath;
	filePath += GaugeParam::kDragon;
	m_faceHandle = LoadGraph((filePath + GaugeParam::kFacePath).c_str());
	filePath = GaugeParam::kFilePath;
	m_backHandle = LoadGraph((filePath + GaugeParam::kBackPath).c_str());
	m_faceBackHandle = LoadGraph((filePath + GaugeParam::kFaceBackPath).c_str());
}


GaugeDragon::~GaugeDragon()
{
	if(m_gauge){
		m_gauge = nullptr;
		delete m_gauge;
	}
	DeleteGraph(m_faceHandle);
	DeleteGraph(m_backHandle);
	DeleteGraph(m_faceBackHandle);
}

void GaugeDragon::Init()
{

}

void GaugeDragon::SetDragon(Dragon * dragon)
{
	// ドラゴンが持っているゲージを配列に設定する
		Vector3 pos = GaugeParam::kDragonGaugePos;

		GaugeShow* gauge = new GaugeShow(pos,GaugeType::HP);
		gauge->SetGauge(dragon->GetGauge());
		m_gauge = gauge;
	
}

void GaugeDragon::End()
{
	if (m_gauge)
		m_gauge->End();
}

void GaugeDragon::Update()
{
	if (m_gauge)
		m_gauge->Update();
}

void GaugeDragon::Draw()
{
	// 描画の中心座標を求める
	Vector3 pos = GaugeParam::kDragonGaugePos;

	Vector3 size = m_gauge->GetGaugeSize() * GaugeParam::kDragonGaugeScale;
	DrawRotaGraph(pos.x, pos.y, GaugeParam::kDragonGaugeScale, 0, m_backHandle, TRUE);
	float posX = m_gauge->GetPosition().x + (size.x * 0.5f) + (GaugeParam::kDragonRadius);
	DrawRotaGraph(posX, GaugeParam::kDragonFacePos.y, GaugeParam::kScale * GaugeParam::kDragonGaugeScale, 0, m_faceBackHandle, TRUE);
	//DrawCircle(posX, pos.y, kRadFrame, GetColor(255, 150, 0), TRUE);
	//DrawCircle(posX, pos.y, kRadius, GetColor(255, 180, 0), TRUE);
	DrawRotaGraph(posX, GaugeParam::kDragonFacePos.y, GaugeParam::kDragonFaceScale * GaugeParam::kDragonGaugeScale, 0, m_faceHandle, TRUE);
	// ゲージの描画処理を行う
		m_gauge->Draw();
}
