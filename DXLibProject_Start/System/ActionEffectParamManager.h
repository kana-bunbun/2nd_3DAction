#pragma once
#include<vector>
class ActionEffectParam;
class ActionEffectParamManager
{
public:
	static ActionEffectParamManager& GetInstance();

	void Load();
	ActionEffectParam GetEffectParam(int ID);
	void End();
private:
	ActionEffectParamManager();
	~ActionEffectParamManager() = default;
	ActionEffectParamManager(const ActionEffectParamManager&) = delete;
	ActionEffectParamManager& operator=(const ActionEffectParamManager&) = delete;
	ActionEffectParamManager(ActionEffectParamManager&&) = delete;
	ActionEffectParamManager& operator=(const ActionEffectParamManager&&) = delete;
private:
	std::vector<ActionEffectParam> m_actionEffectParam;
};

