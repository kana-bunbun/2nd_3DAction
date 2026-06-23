#pragma once
#include<vector>
#include<memory>
class Player;
class Dragon;
class Gauge;

// キャラクター全般のゲージの管理を行う
class CharaGaugeManager
{
public:

	CharaGaugeManager();
	~CharaGaugeManager();

	void Init();
	void Update();
	void End();

	void SetPlayer(Player* pPlayer);
	void SetDragon(Dragon* pDragon);
	std::vector<std::shared_ptr<Gauge>>GetPlayerGauges() { return m_PlayerGauges; }
	std::vector<std::shared_ptr<Gauge>>GetDragonGauges() { return m_DragonGauges; }


private:
	Player* m_pPlayer;
	Dragon* m_pDragon;
	std::vector<std::shared_ptr<Gauge>>m_PlayerGauges;
	std::vector<std::shared_ptr<Gauge>>m_DragonGauges;

};

