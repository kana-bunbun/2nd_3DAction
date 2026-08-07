#include "EffectResourceManager.h"
#include"EffectResource.h"
#include"Data/EffectPathParam.h"
#include"Utility/Loder/CsvLoader.h"
#include<cassert>
#include<EffekseerForDXLib.h>

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
	if(m_resources.contains(ID)) {
		assert(false && "Effect Loaded");
		return false;
	}
	std::string path = kFilePath + GetEffectPath(ID) + kEfkefc;
	int effectHandle = LoadEffekseerEffect(path.c_str());
	auto resouce = std::make_shared<EffectResource>(ID, effectHandle);
	return false;
}

std::shared_ptr<EffectResource> EffectResourceManager::GetResource(int ID) const
{
	return std::shared_ptr<EffectResource>();
}

const std::string& EffectResourceManager::GetEffectPath(int ID)
{
	for (auto& path : m_effectPathParam) {
		if (path.ID != ID)continue;
		return path.effectName;
	}
	return "";
}

