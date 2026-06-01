#include "GaugePlayer.h"
#include "../Character/Player/Player.h"
#include "../../Utility/Game.h"
#include<string>
namespace {
	const char* const kFilePath = "Resource\\UI\\";

	const char* const kPlayer = "Player";
	const char* const kDragon = "Doragon";
	const char* const kFacePath = "Face.png";
	const char* const kBackPath = "GaugeBack.png";
	const char* const kFaceBackPath = "FaceBack.png";

	// 顔画像の描画をする際の単位スケール
	constexpr float kScale = 0.58f;
	// 背景として描画する円の大きさ
	constexpr float kRadius = 360 * kScale;
	// 背景の枠として描画する円の大きさ
	constexpr float kRadFrame = kRadius * 1.1f;
	// ゲージを描画する座標
	constexpr Vector3 kGaugePos = { Game::kScreenWidth - (1000 * Game::kWindowScale), Game::kScreenHeight - (250*Game::kWindowScale), 0 };
	// ゲージ同士の距離
	constexpr float kDiffer = -120 * Game::kWindowScale;
}
GaugePlayer::GaugePlayer():
	m_faceHandle(-1),
	m_gauges()
{
	std::string filePath = kFilePath;
	filePath += kPlayer;
	m_faceHandle = LoadGraph((filePath+kFacePath).c_str());
	filePath = kFilePath;
	m_backHandle = LoadGraph((filePath + kBackPath).c_str());
	m_faceBackHandle = LoadGraph((filePath + kFaceBackPath).c_str());
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
		Vector3 pos=kGaugePos;

		pos.y += kDiffer * (i -0.5f);
		GaugeShow* gauge = new GaugeShow(pos, (GaugeType::Max - 1) - i);
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
	Vector3 size = m_gauges[0]->GetGaugeSize();
	DrawRotaGraph(pos.x, pos.y, 1, 0, m_backHandle, TRUE);
	float posX = pos.x+ (size.x * 0.5f) + (kRadFrame);
	DrawRotaGraph(posX, pos.y, 1, 0, m_faceBackHandle, TRUE);
	//DrawCircle(posX, pos.y, kRadFrame, GetColor(255, 150, 0), TRUE);
	//DrawCircle(posX, pos.y, kRadius, GetColor(255, 180, 0), TRUE);
	DrawRotaGraph(posX, pos.y, kScale, 0, m_faceHandle, TRUE);
	// ゲージの描画処理を行う
	for (auto& gauge : m_gauges)
		gauge->Draw();
}
