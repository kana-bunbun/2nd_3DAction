#pragma once
#include "../GameObject.h"
#include"../UI/Gauge.h"
class Gauge;
class Character :public GameObject
{
public:
	enum class Type {
		Invalid = -1,
		Player,
		Enemy,
		Dragon,
	};
public:
	// キャラクター種類の取得
	virtual const Type& GetCharacterType() {
		return Type::Player;
	}
	// HP取得処理
	Gauge* GetHP() { return m_HPGauge.get(); }
	Gauge* GetMP() { return m_MPGauge.get(); }
	// キャラクターのID
	int m_ID;
	void Damage(float damage)override { m_HPGauge->Decrease(damage); m_HPGauge->Clamp(); }
	void Heal(float heal)override { m_HPGauge->Increase(heal); m_HPGauge->Clamp(); }
protected:
	// HP
	std::unique_ptr<Gauge> m_HPGauge;
	// MP
	std::unique_ptr<Gauge> m_MPGauge;
};

