#pragma once
#include"GaugeShow.h"
#include"CharaGauge.h"
#include<vector>
#include<memory>
/// <summary>
/// プレイヤーのHP・MPを描画する
/// </summary>
class GaugeShow;
class Player;
class HPShow;
class MPShow;
class GaugePlayer:public CharaGauge
{
public:
	GaugePlayer();
	~GaugePlayer();
	void OnInit()override;
	void SetPlayer(Player* player);
	void OnEnd()override;
	void OnUpdate(float deltaTime)override;
	void OnDraw()override;
private:

	// ゲージの配列
	std::unique_ptr<HPShow> m_HPGauge;
	std::unique_ptr<MPShow> m_MPGauge;

};

