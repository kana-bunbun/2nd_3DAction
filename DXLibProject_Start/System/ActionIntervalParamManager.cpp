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
	m_intervalParam = Data::Csv::LoadCsvAs<ActionIntervalParam>(kDataName);
}

const ActionIntervalParam& ActionIntervalParamManager::GetActionIntervalParam(int ID)
{
	ActionIntervalParam param;
	if (ID < 0)return param;
	for (auto& interval : m_intervalParam) {
		if (interval.ID != ID)continue;
		param = interval;
		break;
	}
	return param;
}
