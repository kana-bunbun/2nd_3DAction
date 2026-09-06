#include"pch.h"
#include "ActionEffectParamManager.h"
#include "../Data/ActionEffectParam.h"
#include "../Utility/Loder/Data.h"
#include "../Utility/Loder/CsvLoader.h"

namespace {
    const char* const kActionEffectParamData = "ActionEffectParam";
}
ActionEffectParamManager& ActionEffectParamManager::GetInstance()
{
    static ActionEffectParamManager instance;
    return instance;
}

ActionEffectParamManager::ActionEffectParamManager()
{
    Load();
}
void ActionEffectParamManager::Load()
{
    // 読み込む
    m_actionEffectParam = Data::Csv::LoadCsvAs<ActionEffectParam>(kActionEffectParamData);
}

const ActionEffectParam& ActionEffectParamManager::GetEffectParam(int ID)
{
    ActionEffectParam param;
    // 指定した値が不正な値かチェック
    if (ID<0)return param;

    for (int i = 0; i < m_actionEffectParam.size(); i++) {
        // IDが一致するものを探す
        if (m_actionEffectParam[i].ID != ID)continue;
        param=m_actionEffectParam[i];
        break;
    }
    return param;
}

void ActionEffectParamManager::End()
{}

