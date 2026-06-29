#pragma once
#include<string>
#include<vector>
#include"../World/Character/AnimationController.h"
#include"../World/Character/Animation.h"
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
		Map,
		Graph,
		CSV,
		Max,
	};
public:
	class GraphData {			// 画像のデータ
	public:
		int graphHandle=-1;		// グラフィックハンドル
		std::string graphName;	// データの名前
	};
	class ModelData {			// モデルのデータ
	public:
		int modelHandle=-1;		// モデルハンドル
		std::string modelName;	// データの名前
		AnimationController anim;// アニメーション管理
	};
public:
	void End();
	static ResourceManager& GetInstance();
	/// <summary>
	/// グラフィックハンドルを取得する関数
	/// </summary>
	int GetGraph(std::string graphName);
	/// <summary>
	/// モデルハンドルのみを取得する関数
	/// </summary>
	int GetModel(std::string modelName,FileName modelType);
	ResourceManager::ModelData GetModelCSV(std::string csvName);

private:

	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&)=delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;
private:
	std::vector<GraphData>m_graphData;
	std::vector<ModelData>m_modelData;
};

