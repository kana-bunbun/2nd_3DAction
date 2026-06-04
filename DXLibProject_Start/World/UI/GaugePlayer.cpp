#include "GaugePlayer.h"
#include "../Character/Player/Player.h"
#include "../../Utility/Game.h"
#include"GaugeShow.h"
#include"GaugeParam.h"
#include<string>

GaugePlayer::GaugePlayer():
	m_gauges()
{
	std::string filePath = GaugeParam::kFilePath;
	filePath += GaugeParam::kPlayer;
	m_faceHandle = LoadGraph((filePath+ GaugeParam::kFacePath).c_str());
	filePath = GaugeParam::kFilePath;
	m_backHandle = LoadGraph((filePath + GaugeParam::kBackPath).c_str());
	m_faceBackHandle = LoadGraph((filePath + GaugeParam::kFaceBackPath).c_str());
}

GaugePlayer::~GaugePlayer()
{
	for (auto& gauge : m_gauges) {
		gauge = nullptr;
		delete gauge;
	}
	DeleteGraph(m_faceHandle);
	DeleteGraph(m_backHandle);
	DeleteGraph(m_faceBackHandle);
}

void GaugePlayer::Init()
{
}

void GaugePlayer::SetPlayer(Player* player)
{
	// プレイヤーが持っているゲージを配列に設定する
	for (int i = 0; i < GaugeType::Max; i++) {
		Vector3 pos= GaugeParam::kPlayerGaugePos;

		pos.y -= GaugeParam::kDiffer * (i -0.5f);
		GaugeShow* gauge = new GaugeShow(pos, /*(GaugeType::Max - 1) - */i);
		gauge->SetGauge(player->GetGauge(i));
		m_gauges[i] = gauge;
	}
}

void GaugePlayer::End()
{
	// ゲージの終了処理を行う
	for (auto& gauge : m_gauges)
		gauge->End();
}

void GaugePlayer::Update()
{
	// ゲージの更新処理を行う
	for (auto& gauge : m_gauges)
		gauge->Update();
}

void GaugePlayer::Draw()
{
	// 描画の中心座標を求める
	Vector3 pos = (m_gauges[0]->GetPosition() + m_gauges[1]->GetPosition())*0.5f;
	Vector3 size = m_gauges[0]->GetGaugeSize()* GaugeParam::kPlayerGaugeScale;
	DrawRotaGraph(pos.x, GaugeParam::kPlayerGaugePos.y, GaugeParam::kPlayerGaugeScale, 0, m_backHandle, TRUE);
	float posX = m_gauges[0]->GetPosition().x+ (size.x * 0.5f) + (GaugeParam::kPlayerRadius);
	DrawRotaGraph(posX, GaugeParam::kPlayerFacePos.y, GaugeParam::kScale*GaugeParam::kPlayerGaugeScale, 0, m_faceBackHandle, TRUE);
	//DrawCircle(posX, pos.y, kRadFrame, GetColor(255, 150, 0), TRUE);
	//DrawCircle(posX, pos.y, kRadius, GetColor(255, 180, 0), TRUE);
	DrawRotaGraph(posX, GaugeParam::kPlayerFacePos.y, GaugeParam::kPlayerFaceScale* GaugeParam::kPlayerGaugeScale, 0, m_faceHandle, TRUE);
	// ゲージの描画処理を行う
	for (auto& gauge : m_gauges)
		gauge->Draw();
}
