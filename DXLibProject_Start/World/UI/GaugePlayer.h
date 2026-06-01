#pragma once
#include"GaugeShow.h"
#include<array>
#include<vector>
/// <summary>
/// プレイヤーのHP・MPを描画する
/// </summary>
class GaugeShow;
class Player;
class GaugePlayer
{
public:
	GaugePlayer();
	~GaugePlayer();
	void Init();
	void SetPlayer(Player* player);
	void End();
	void Update();
	void Draw();
private:
	// プレイヤーの顔画像
	int m_faceHandle;
	// 背景の画像
	int m_backHandle;
	int m_faceBackHandle;
	// ゲージの配列
	std::array<GaugeShow*, GaugeType::Max>m_gauges;
};

