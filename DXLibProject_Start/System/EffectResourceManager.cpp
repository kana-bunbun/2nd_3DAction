#include"pch.h"
#include "EffectResourceManager.h"
#include"EffectResource.h"
#include"Data/EffectPathParam.h"
#include"Utility/Loder/CsvLoader.h"

namespace {
	const char* const kFilePath = "Resource\\Effect\\";
	const char* const kEfkefc = ".efkefc";
	const char* const kResourcePath = "EffectPathParam";
}
EffectResourceManager::EffectResourceManager()
{
	m_effectPathParam = Data::Csv::LoadCsvAs<EffectPathParam>(kResourcePath);
	for (int i = 0; i < m_effectPathParam.size(); i++) {
		LoadEffect(m_effectPathParam[i].ID);
	}
}

EffectResourceManager::~EffectResourceManager()
{
}

bool EffectResourceManager::LoadEffect(int ID)
{
	// “¯–¼‚Ì“o˜^‚ð–hŽ~‚·‚é
	// Žw’è‚µ‚½–¼‘O‚ª‚·‚Å‚Émap‚ÉŠÜ‚Ü‚ê‚Ä‚¢‚é‚©ƒ`ƒFƒbƒN‚·‚é
	if(m_resources.contains(ID)) {
		assert(false && "Effect Loaded");
		return false;
	}
	// ƒpƒX‚Ìì¬
	EffectPathParam param = GetEffectParam(ID);
	std::string path = kFilePath + param.effectName + kEfkefc;
	int effectHandle = LoadEffekseerEffect(path.c_str(), param.scale);
	auto resouce = std::make_shared<EffectResource>(ID, effectHandle,param.isChace);
	m_resources[ID] = resouce;
	return true;
}

std::shared_ptr<EffectResource> EffectResourceManager::GetResource(int ID) const
{
	auto it = m_resources.find(ID);
	if (it == m_resources.end()) {
		// ‹ó‚ð•Ô‚·
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

