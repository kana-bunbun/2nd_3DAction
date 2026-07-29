#include "ExternalDataManager.h"
#include"../Utility/Loder/CsvLoader.h"
#include"../World/GameObjectParam.h"
namespace {
	// プレイヤーのパス情報のデータ名
	const char* const kPlayerModelPath = "PlayerModelPath";

	const char* const kModelPath[static_cast<int>(ModelName::Max)]{
		"PlayerModel",
		"DragonModel",
		"EnemyModel",
		"WallModel",
		"FloorModel",
		"StairModel",
	};
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
	// モデルのパス情報
	for (int i = 0; i < m_modelPathParam.size(); i++) {
		m_modelPathParam[i] = Data::Csv::LoadCsvAs<ModelPathParam>(kModelPath[i])[0];
	}
}

void ExternalDataManager::Init()
{

}

void ExternalDataManager::End()
{

}
