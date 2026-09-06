#include "pch.h"
#include "GaugeDragon.h"
#include "GaugeParam.h"
#include"../../System/ImageManager.h"
#include"../Character/Guardian/Dragon.h"
#include"../../Utility/Vector3.h"
namespace {
	// ドラゴンの顔画像のパスID
	constexpr int kDragonFaceGraphID = 2003;

}

GaugeDragon::GaugeDragon() :
	m_gauge()
{
	std::string filePath = GaugeParam::kFilePath;
	filePath += GaugeParam::kDragon;
	m_faceImage = ImageManager::GetInstance().GetImage(kDragonFaceGraphID);
	filePath = GaugeParam::kFilePath;
	m_backImage = ImageManager::GetInstance().GetImage(kGaugeBackGraphID);
	m_faceBackImage = ImageManager::GetInstance().GetImage(kFaceBackGraphID);
}


GaugeDragon::~GaugeDragon()
{
	if(m_gauge){
		m_gauge = nullptr;
		delete m_gauge;
	}
}

void GaugeDragon::OnInit()
{

}

void GaugeDragon::SetDragon(Dragon * dragon)
{
	// ドラゴンが持っているゲージを配列に設定する
		Vector3 pos = GaugeParam::kDragonGaugePos;

		GaugeShow* gauge = new GaugeShow(pos);
		m_gauge = gauge;
	
}

void GaugeDragon::OnEnd()
{
	if (m_gauge)
		m_gauge->End();
}

void GaugeDragon::OnUpdate(float deltaTime, const InputData& inputData)
{
	if (m_gauge)
		m_gauge->Update(deltaTime);
}

void GaugeDragon::OnDraw()
{
	// 描画の中心座標を求める
	Vector3 pos = GaugeParam::kDragonGaugePos;

	Vector3 size = m_gauge->GetGaugeSize() * GaugeParam::kDragonGaugeScale;
	DrawRotaGraph(pos.x, pos.y, GaugeParam::kDragonGaugeScale, 0, m_backImage->GetHandle(), TRUE);
	float posX = m_gauge->GetPosition().x + (size.x * 0.5f) + (GaugeParam::kDragonRadius);
	DrawRotaGraph(posX, GaugeParam::kDragonFacePos.y, GaugeParam::kScale * GaugeParam::kDragonGaugeScale, 0, m_faceBackImage->GetHandle(), TRUE);
	//DrawCircle(posX, pos.y, kRadFrame, GetColor(255, 150, 0), TRUE);
	//DrawCircle(posX, pos.y, kRadius, GetColor(255, 180, 0), TRUE);
	DrawRotaGraph(posX, GaugeParam::kDragonFacePos.y, GaugeParam::kDragonFaceScale * GaugeParam::kDragonGaugeScale, 0, m_faceImage->GetHandle(), TRUE);
	// ゲージの描画処理を行う
		m_gauge->Draw();
}
