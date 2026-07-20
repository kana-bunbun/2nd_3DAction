#include "Resource.h"
#include<DxLib.h>
#include"ResourceManager.h"
#include"../Utility/CsvLoader.h"
#include"../Data/ModelPathParam.h"
namespace {
	// データ読み込み時の不正値
	constexpr int kHandleInvalidValue = -1;
}

ModelData::ModelData(std::string path)
{
	// データの読み込み
	Load(path);
}

ModelData::~ModelData()
{
	// データの破棄
	Delete();
}

ModelData* ModelData::Duplicate()
{
	if (m_handle)return nullptr;
	ModelData* modelData = new ModelData(m_name);
	modelData->m_name = m_name;
	modelData->m_handle = MV1DuplicateModel(m_handle);
	for (int i = 0; i < m_animHandle.size(); i++) {
		modelData->m_animHandle[i] = MV1DuplicateModel(m_animHandle[i]);
	}
	return modelData;
}

void ModelData::Load(std::string path)
{
	ModelPathParam pathParam = Data::Csv::LoadCsvAs<ModelPathParam>(path)[0];
	m_name = path;
	m_handle = MV1LoadModel(pathParam.modelPath.c_str());
	for (int i = 0; i < pathParam.modelPath.size(); i++) {
		m_animHandle.emplace_back(MV1LoadModel(pathParam.animationPath[i].c_str()));
	}
}

void ModelData::Delete()
{
	MV1DeleteModel(m_handle);
	for (int i = 0; i < m_animHandle.size(); i++) {
		MV1DeleteModel(m_animHandle[i]);
		m_animHandle[i] = kHandleInvalidValue;
	}
	m_handle = kHandleInvalidValue;
	m_name = "";
}

GraphData::GraphData(std::string path)
{
	// データの読み込み
	Load(path);
}

GraphData::~GraphData()
{
	// データの破棄
	Delete();
}

void GraphData::Load(std::string path)
{
	m_handle = kHandleInvalidValue;
	path = kResourcePath + kDataPath[static_cast<int>(ResourceManager::FileName::Graph)] + path + kPng;
	m_handle = LoadGraph(path.c_str());
}

void GraphData::Delete()
{
	if (m_handle == kHandleInvalidValue)return;
	DeleteGraph(m_handle);
	m_handle = kHandleInvalidValue;
	m_name = "";
}