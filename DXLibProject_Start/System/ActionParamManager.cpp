#include "ActionParamManager.h"
#include "../Data/ActionParam.h"
#include"../Utility/Loder/CsvLoader.h"

namespace {
	const char* const kDataName = "ActionParam";
}

ActionParamManager& ActionParamManager::GetInstance()
{
	static ActionParamManager instance;
	return instance;
}

ActionParamManager::ActionParamManager()
{
	Load();
}

void ActionParamManager::Load()
{
	m_actionParam = Data::Csv::LoadCsvAs<ActionParam>(kDataName);
}

const ActionParam& ActionParamManager::GetActionParam(int ID)
{
	ActionParam param;
	if (ID < 0)return param;

	for (auto& actionParam : m_actionParam) {
		if (ID != actionParam.ID)continue;
		param = actionParam;
		break;
	}
	return param;
}

void ActionParamManager::End()
{}

