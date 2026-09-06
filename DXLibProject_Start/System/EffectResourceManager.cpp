#include"pch.h"
#include "EffectResourceManager.h"
#include"EffectResource.h"
#include"Data/EffectPathParam.h"
#include"Utility/Loder/CsvLoader.h"

namespace {
	const char* const kFilePath = "\\Resource\\Effect\\";
	const char* const kEfkefc = ".efkefc";
	const char* const kResourcePath = "EffectPathParam";
}
EffectResourceManager::EffectResourceManager()
{
	m_effectPathParam = Data::Csv::LoadCsvAs<EffectPathParam>(kResourcePath);
}

EffectResourceManager::~EffectResourceManager()
{
}

bool EffectResourceManager::LoadEffect(int ID)
{
	// 同名の登録を防止する
	// 指定した名前がすでにmapに含まれているかチェックする
	if(m_resources.contains(ID)) {
		assert(false && "Effect Loaded");
		return false;
	}
	// パスの作成
	EffectPathParam param = GetEffectParam(ID);
	std::string path = kFilePath + param.effectName + kEfkefc;
	int effectHandle = LoadEffekseerEffect(path.c_str(), param.scale);
	auto resouce = std::make_shared<EffectResource>(ID, effectHandle);
	m_resources[ID] = resouce;
	return true;
}

std::shared_ptr<EffectResource> EffectResourceManager::GetResource(int ID) const
{
	auto it = m_resources.find(ID);
	if (it == m_resources.end()) {
		// 空を返す
		return nullptr;
	}

	return it->second;
}

const EffectPathParam& EffectResourceManager::GetEffectParam(int ID)
{
	for (auto& effectParam : m_effectPathParam) {
		if (effectParam.ID != ID)continue;
		return effectParam;
	}
	return EffectPathParam();
}

