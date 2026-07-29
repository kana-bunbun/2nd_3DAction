#include "ActionIntervalParamManager.h"
#include "../Utility/Loder/CsvLoader.h"
namespace {
	const char* const kDataName = "ActionIntervalParam";
}
ActionIntervalParamManager& ActionIntervalParamManager::GetInstance()
{
	static ActionIntervalParamManager instance;
	return instance;
}
ActionIntervalParamManager::ActionIntervalParamManager()
{
	Load();
}

ActionIntervalParamManager::~ActionIntervalParamManager()
{

}


void ActionIntervalParamManager::Load()
{

}

const ActionIntervalParam& ActionIntervalParamManager::GetActionIntervalParam(int ID)
{
	ActionIntervalParam param;
	if (ID < 0 || ID >= m_intervalParam.size())return param;
	param = m_intervalParam[ID];
	return param;
}
