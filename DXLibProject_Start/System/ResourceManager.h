#pragma once

#include"../World/Character/AnimationController.h"
#include"../World/Character/Animation.h"
#include"../Utility/Loder/Data.h"
#include"../Utility/ModelData.h"
#include"Resource.h"

/// <summary>
/// 画像やモデル等のリソースを管理するクラス
/// シングルトンとして運用する
/// </summary>
class ResourceManager
{
public:
	enum class FileName {
		Invalid=-1,
		Player,
		Doragon,
		Enemy,
		Item,
		Map,
		Graph,
		CSV,
		Max,
	};

public:
	~ResourceManager();
	void End();
	static ResourceManager& GetInstance();
	/// <summary>
	/// グラフィックハンドルを取得する関数
	/// </summary>
	GraphData* GetGraph(std::string dataName);
	/// <summary>
	/// モデルハンドルのみを取得する関数
	/// </summary>
	ModelData* GetModel(std::string dataName);
	

private:

	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&)=delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;
private:
	// ModelDataのDuplicate関数から生ポインタを追加したい
	std::vector<GraphData*>m_graphData;
	std::vector<ModelData*> m_modelData;
	std::vector<ModelData*> m_DuplicateList;
};
namespace {
	const char* const kDataPath = "Data\\";
	const char* const kCsv = ".csv";
	const char* const kResourcePath = "Resource\\";
	const char* const kFilePath[static_cast<int>(ResourceManager::FileName::Max)] = {
		"Player\\",
		"Doragon\\",
		"Enemy\\",
		"Item\\",
		"Map\\",
		"Graph\\",
		"CSV\\",
	};
	const char* const kAnimation = "Animation\\";
	const char* const kPng = ".png";
	const char* const kMv1 = ".mv1";
}