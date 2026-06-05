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

	void SetPlayer(std::shared_ptr<Player> pPlayer);
	void SetDragon(std::shared_ptr<Dragon> pDragon);
	std::vector<std::shared_ptr<Gauge>>GetPlayerGauges() { return m_PlayerGauges; }
	std::vector<std::shared_ptr<Gauge>>GetDragonGauges() { return m_DragonGauges; }

private:
	std::shared_ptr<Player>m_pPlayer;
	std::shared_ptr<Dragon>m_pDragon;
	std::vector<std::shared_ptr<Gauge>>m_PlayerGauges;
	std::vector<std::shared_ptr<Gauge>>m_DragonGauges;

};

