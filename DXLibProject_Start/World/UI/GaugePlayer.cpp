#include "GaugePlayer.h"
#include "../Character/Player/Player.h"
#include "../../Utility/Game.h"
#include"../../System/ImageManager.h"
#include"GaugeShow.h"
#include"HPShow.h"
#include"MPShow.h"
#include"GaugeParam.h"
#include<string>

namespace{
	// プレイヤー顔画像のパスID
	constexpr int kPlayerFaceGraphID = 2002;

}

GaugePlayer::GaugePlayer():
	m_HPGauge(nullptr),
	m_MPGauge(nullptr)
{
	// キャラクターの顔画像の読み込み
	m_faceImage = ImageManager::GetInstance().GetImage(kPlayerFaceGraphID);
	// ゲージの背景画像の読み込み
	m_backImage = ImageManager::GetInstance().GetImage(kGaugeBackGraphID);
	m_faceBackImage = ImageManager::GetInstance().GetImage(kFaceBackGraphID);
}

GaugePlayer::~GaugePlayer()
{
}

void GaugePlayer::Init()
{
}

void GaugePlayer::SetPlayer(Player* player)
{

		Vector3 pos= GaugeParam::kPlayerGaugePos;
		int hp = static_cast<int>(GaugeType::HP), mp = static_cast<int>(GaugeType::MP);
		pos.y -= GaugeParam::kDiffer * (static_cast<int>(GaugeType::HP) - 0.5f);
		m_HPGauge = std::make_unique<HPShow>(pos);
		pos = GaugeParam::kPlayerGaugePos;
		pos.y -= GaugeParam::kDiffer * (static_cast<int>(GaugeType::MP) - 0.5f);
		m_MPGauge = std::make_unique<MPShow>(pos);

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
	DrawRotaGraph(pos.x, GaugeParam::kPlayerGaugePos.y, GaugeParam::kPlayerGaugeScale, 0, m_backImage->GetHandle(), TRUE);
	float posX = m_HPGauge->GetPosition().x+ (size.x * 0.5f) + (GaugeParam::kPlayerRadius);
	DrawRotaGraph(posX, GaugeParam::kPlayerFacePos.y, GaugeParam::kScale*GaugeParam::kPlayerGaugeScale, 0, m_faceBackImage->GetHandle(), TRUE);
	//DrawCircle(posX, pos.y, kRadFrame, GetColor(255, 150, 0), TRUE);
	//DrawCircle(posX, pos.y, kRadius, GetColor(255, 180, 0), TRUE);
	DrawRotaGraph(posX, GaugeParam::kPlayerFacePos.y, GaugeParam::kPlayerFaceScale* GaugeParam::kPlayerGaugeScale, 0, m_faceImage->GetHandle(), TRUE);
	// ゲージの描画処理を行う
	m_HPGauge->Draw();
	m_MPGauge->Draw();
}
