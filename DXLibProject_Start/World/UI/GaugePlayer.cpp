#include "GaugePlayer.h"
#include "../Character/Player/Player.h"
#include "../../Utility/Game.h"
#include"GaugeShow.h"
#include"GaugeParam.h"
#include<string>

GaugePlayer::GaugePlayer():
	m_HPGauge(nullptr),
	m_MPGauge(nullptr)
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
	
	DeleteGraph(m_faceHandle);
	DeleteGraph(m_backHandle);
	DeleteGraph(m_faceBackHandle);
}

void GaugePlayer::Init()
{
}

void GaugePlayer::SetPlayer(Player* player)
{

		Vector3 pos= GaugeParam::kPlayerGaugePos;
		int hp = static_cast<int>(GaugeType::HP), mp = static_cast<int>(GaugeType::MP);
		pos.y -= GaugeParam::kDiffer * (static_cast<int>(GaugeType::HP) - 0.5f);
		GaugeShow* hpGauge = new GaugeShow(pos, hp);
		hpGauge->SetGauge(player->GetHP());
		m_HPGauge = hpGauge;
		pos = GaugeParam::kPlayerGaugePos;
		pos.y -= GaugeParam::kDiffer * (static_cast<int>(GaugeType::MP) - 0.5f);
		GaugeShow* mpGauge = new GaugeShow(pos, mp);
		mpGauge->SetGauge(player->GetMP());
		m_MPGauge = mpGauge;

	// プレイヤーが持っているゲージを配列に設定する
	for (int i = 0; i < GaugeType::Max; i++) {
	}
}

void GaugePlayer::End()
{
	// ゲージの終了処理を行う
	m_HPGauge->End();
	m_MPGauge->End();

}

void GaugePlayer::Update(float deltaTime)
{
	// ゲージの更新処理を行う
	m_HPGauge->Update(deltaTime);
	m_MPGauge->Update(deltaTime);
}

void GaugePlayer::Draw()
{
	// 描画の中心座標を求める
	Vector3 pos = (m_HPGauge->GetPosition() + m_MPGauge->GetPosition())*0.5f;
	Vector3 size = m_HPGauge->GetGaugeSize()* GaugeParam::kPlayerGaugeScale;
	DrawRotaGraph(pos.x, GaugeParam::kPlayerGaugePos.y, GaugeParam::kPlayerGaugeScale, 0, m_backHandle, TRUE);
	float posX = m_HPGauge->GetPosition().x+ (size.x * 0.5f) + (GaugeParam::kPlayerRadius);
	DrawRotaGraph(posX, GaugeParam::kPlayerFacePos.y, GaugeParam::kScale*GaugeParam::kPlayerGaugeScale, 0, m_faceBackHandle, TRUE);
	//DrawCircle(posX, pos.y, kRadFrame, GetColor(255, 150, 0), TRUE);
	//DrawCircle(posX, pos.y, kRadius, GetColor(255, 180, 0), TRUE);
	DrawRotaGraph(posX, GaugeParam::kPlayerFacePos.y, GaugeParam::kPlayerFaceScale* GaugeParam::kPlayerGaugeScale, 0, m_faceHandle, TRUE);
	// ゲージの描画処理を行う
	m_HPGauge->Draw();
	m_MPGauge->Draw();
}
