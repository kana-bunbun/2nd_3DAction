#pragma once
#include<vector>
#include"../Data/ActionIntervalParam.h"
class ActionIntervalParamManager
{
public:
	static ActionIntervalParamManager& GetInstance();
	void Load();
	const ActionIntervalParam& GetActionIntervalParam(int ID);
private:
	ActionIntervalParamManager();
	~ActionIntervalParamManager();

	ActionIntervalParamManager(const ActionIntervalParamManager&) = delete;
	ActionIntervalParamManager operator=(const ActionIntervalParamManager&) = delete;
	ActionIntervalParamManager(ActionIntervalParamManager&&) = delete;
	ActionIntervalParamManager operator=(const ActionIntervalParamManager&&) = delete;

private:
	std::vector<ActionIntervalParam> m_intervalParam;
};

