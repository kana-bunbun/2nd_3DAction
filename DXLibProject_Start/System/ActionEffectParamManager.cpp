#include "ActionEffectParamManager.h"
#include "../Data/ActionEffectParam.h"
#include "../Utility/Data.h"
#include "../Utility/CsvLoader.h"

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
    // 一旦読み込む
    std::vector<ActionEffectParam> actionEffects = Data::Csv::LoadCsvAs<ActionEffectParam>(kActionEffectParamData);
    // 最大のIDを取得
    int reserveNum = actionEffects[actionEffects.size() - 1].ID+1;
    // 要素数を確保
    m_actionEffectParam.reserve(reserveNum);
    ActionEffectParam param=ActionEffectParam();
    // 配列の要素を初期化
    for (int i = 0; i < reserveNum; i++) {
        m_actionEffectParam.emplace_back(param);
    }
    // IDと一致する要素の番号に格納
    for (auto& actionEffect : actionEffects) {
        m_actionEffectParam[actionEffect.ID] = actionEffect;
    }
}

ActionEffectParam ActionEffectParamManager::GetEffectParam(int ID)
{
    ActionEffectParam param;
    if (ID<0 || ID>m_actionEffectParam.size())return param;
    param = m_actionEffectParam[ID];
    return param;
}

void ActionEffectParamManager::End()
{}

