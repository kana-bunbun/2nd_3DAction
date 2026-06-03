#pragma once
class DragonAttack
{
public:
	DragonAttack();
	~DragonAttack();
	void Init();
	void Update();
	void End();
	bool GetAttackFlag() { return m_attackFlag; }
	bool GetActive() { return m_active; }
	int GetCount() { return m_attackCount; }
	void ResetCount() { m_attackCount = 0.0f; }
private:
	bool m_active;
	bool m_attackFlag;
	int m_attackCount;
};

