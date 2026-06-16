#pragma once
#include"CharaGauge.h"
class GaugeShow;
class Dragon;
/// <summary>
/// ドラゴンのHPの描画をする
/// </summary>
class GaugeDragon:public CharaGauge
{
public:
	GaugeDragon();
	~GaugeDragon();
	
	void Init()override;
	void SetDragon(Dragon* dragon);
	void End()override;
	void Update(float deltaTime)override;
	void Draw()override;
private:
	// ゲージのポインタ
	GaugeShow* m_gauge;
};

