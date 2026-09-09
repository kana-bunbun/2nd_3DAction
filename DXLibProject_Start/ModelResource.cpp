#include "pch.h"
#include "ModelResource.h"
#include"System/Resource.h"
#include"Data/ModelPathParam.h"
#include"System/ResourceManager.h"
namespace {
}
ModelResource::ModelResource(const std::string& dataName):
	m_dataName(dataName)
{
}

ModelResource::~ModelResource()
{
}

bool ModelResource::Load()
{
	if (IsLoaded()) return false;
	ResourceManager::GetInstance().GetModel(m_dataName);
	return true;
}

bool ModelResource::IsLoaded() const
{
	return m_modelData->GetHandle() != -1;
}

int ModelResource::GetModelHandle() const
{
	return m_modelData->GetHandle();
}
