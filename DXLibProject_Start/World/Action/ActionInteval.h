#pragma once
#include<string>
/// <summary>
///  効果発動のタイミングを指示する
/// </summary>
class ActionInteval
{
public:
	ActionInteval();
	~ActionInteval();
	void Init(const std::string& dataName);
	void Setup();
	void Update(float deltaTime);
	bool IsFinish();
private:

	float m_effectCount;
	float m_intervalCount;
};

