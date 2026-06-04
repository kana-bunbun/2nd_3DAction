#pragma once
#include"../../Utility/Vector3.h"
#include<memory>
#include<vector>
class GaugePlayer;
class GaugeDragon;
class Player;
class Dragon;
// UIの
class UIManager
{
public:
	UIManager();
	~UIManager();
	void Init();
	void End();
	void Update();
	void Draw();

	/// <summary>
	/// プレイヤーのポインタを設定する関数
	/// </summary>
	/// <param name="pPlayer"></param>
	void SetPlayer(Player* pPlayer);
	void SetDragon(Dragon* pDragon);
private:
	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	Player* m_pPlayer;
	Dragon* m_pDragon;
	/// <summary>
	/// プレイヤーのゲージ
	/// </summary>
	std::unique_ptr<GaugePlayer>m_gaugePlayer;
	std::unique_ptr<GaugeDragon>m_gaugeDragon;
};

