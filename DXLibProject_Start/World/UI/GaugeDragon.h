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
	
	void OnInit()override;
	void SetDragon(Dragon* dragon);
	void OnEnd()override;
	void OnUpdate(float deltaTime, const InputData& _inputData)override;
	void OnDraw()override;
private:
	// ゲージのポインタ
	GaugeShow* m_gauge;
};

