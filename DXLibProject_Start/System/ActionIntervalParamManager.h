#pragma once
#include<vector>
#include"../Data/ActionIntervalParam.h"
class ActionIntervalParamManager
{
public:
	ActionIntervalParamManager();
	~ActionIntervalParamManager();
	void Load();
	const ActionIntervalParam& GetActionIntervalParam(int ID);
private:
	std::vector<ActionIntervalParam> m_intervalParam;
};

