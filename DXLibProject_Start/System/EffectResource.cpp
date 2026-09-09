#include"pch.h"
#include "EFfectResource.h"
#include"EffectResourceManager.h"
namespace {
	const char* const kFilePath = "Resource\\Effect\\";
	const char* const kExtension = ".efkefc";
}
EffectResource::EffectResource(const EffectPathParam& param):
	m_ID(param.ID),
	m_param(param),
	m_handle(-1),
	m_isChace(param.isChace)
{
	Load();
}

EffectResource::~EffectResource()
{
	DeleteEffekseerEffect(m_handle);
}
bool EffectResource:: Load() {
	if (IsLoaded()) return false;
	std::string path = kFilePath + m_param.effectName + kExtension;
	m_handle = LoadEffekseerEffect(path.c_str(), m_param.scale);
	return true;
}
