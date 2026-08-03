#pragma once
#include"GaugeShow.h"
#include"CharaGauge.h"
#include<array>
#include<vector>
/// <summary>
/// プレイヤーのHP・MPを描画する
/// </summary>
class GaugeShow;
class Player;
class GaugePlayer:public CharaGauge
{
public:
	GaugePlayer();
	~GaugePlayer();
	void Init()override;
	void SetPlayer(Player* player);
	void End()override;
	void Update(float deltaTime)override;
	void Draw()override;
private:

	// ゲージの配列
	std::unique_ptr<HPShow> m_HPGauge;
	std::unique_ptr<MPShow> m_MPGauge;

};

