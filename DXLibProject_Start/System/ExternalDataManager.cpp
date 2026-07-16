#include "ExternalDataManager.h"
#include"../Utility/CsvLoader.h"
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
	// プレイヤーモデルのパス情報
	m_playerPathParam = Data::Csv::LoadCsvAs<ModelPathParam>(kPlayerModelPath)[0];
}

void ExternalDataManager::Init()
{

}

void ExternalDataManager::End()
{

}
