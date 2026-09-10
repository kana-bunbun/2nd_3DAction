#include "pch.h"
#include "StagePartDatabase.h"

void StagePartDatabase::Register(const std::string& partName, const Stage::PartData& data)
{
    m_stagePartDatabase[partName] = data;
}

const Stage::PartData* StagePartDatabase::GetData(const std::string & partName) const
{
    auto it = m_stagePartDatabase.find(partName);

    if (it == m_stagePartDatabase.end())return nullptr;

    return &it->second;
}
