#include "ExternalDataManager.h"
#include"../Utility/CsvLoader.h"

namespace {
	// プレイヤーのパス情報のデータ名
	const char* const kPlayerModelPath = "PlayerModelPath";
}
ExternalDataManager::ExternalDataManager()
{
	LoadAll();
}

ExternalDataManager::~ExternalDataManager()
{

}

void ExternalDataManager::LoadAll()
{
	// プレイヤーモデルのパス情報
	m_playerPathParam = Data::Csv::LoadCsvAs<ModelPathParam>(kPlayerModelPath)[0];
}

void ExternalDataManager::Init()
{

}

void ExternalDataManager::End()
{

}
