#include "GaugePlayer.h"
#include "../Character/Player/Player.h"
#include "../../Utility/Game.h"
#include"GaugeShow.h"
#include"GaugeParam.h"
#include<string>
namespace {
	const char* const kFilePath = "Resource\\UI\\";

	const char* const kPlayer = "Player";
	const char* const kDragon = "Doragon";
	const char* const kFacePath = "Face.png";
	const char* const kBackPath = "GaugeBack.png";
	const char* const kFaceBackPath = "FaceBack.png";

	// 顔画像の描画をする際の単位スケール
	constexpr float kScale = 1.2f;
	constexpr float kFaceScale = 0.77f*kScale;
	// 背景として描画する円の大きさ
	constexpr float kRadius = 310 * kFaceScale* GaugeParam::kInitScale;
	// 背景の枠として描画する円の大きさ
	// ゲージを描画する座標
	constexpr Vector3 kGaugePos = { Game::kScreenWidth - (1200 * GaugeParam::kInitScale), Game::kScreenHeight - (250*GaugeParam::kInitScale), 0 };
	// ゲージ同士の距離
	constexpr float kDiffer = -150 * GaugeParam::kInitScale;
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
	Vector3 size = m_gauges[0]->GetGaugeSize()* GaugeParam::kInitScale;
	DrawRotaGraph(pos.x, pos.y, GaugeParam::kInitScale, 0, m_backHandle, TRUE);
	float posX = m_gauges[1]->GetPosition().x+ (size.x * 0.5f) + (kRadius);
	DrawRotaGraph(posX, m_gauges[1]->GetPosition().y, kScale*GaugeParam::kInitScale, 0, m_faceBackHandle, TRUE);
	//DrawCircle(posX, pos.y, kRadFrame, GetColor(255, 150, 0), TRUE);
	//DrawCircle(posX, pos.y, kRadius, GetColor(255, 180, 0), TRUE);
	DrawRotaGraph(posX, m_gauges[1]->GetPosition().y, kFaceScale* GaugeParam::kInitScale, 0, m_faceHandle, TRUE);
	// ゲージの描画処理を行う
	for (auto& gauge : m_gauges)
		gauge->Draw();
}
