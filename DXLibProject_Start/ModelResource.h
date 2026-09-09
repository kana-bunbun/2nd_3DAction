#pragma once
#include"pch.h"
#include"Data/ModelPathParam.h"
class ModelData;
class ModelResource
{
public:
	ModelResource(const std::string& dataName);
	~ModelResource();

	// ëfçﬁÇÉRÉsÅ[Ç≥ÇÍÇÈÇ±Ç∆ÇñhÇÆ
	ModelResource(const ModelResource&) = delete;
	ModelResource& operator=(const ModelResource&) = delete;
	ModelResource(ModelResource&&) = delete;
	ModelResource& operator=(const ModelResource&&) = delete;

	// ì«Ç›çûÇ›
	bool Load();

	bool IsLoaded()const;
	int GetModelHandle()const;
	const std::string& GetParam()const { return m_dataName; }
private:
	ModelData* m_modelData;
	std::string m_dataName;
};

