#pragma once
#include<string>
#include<vector>
#include"../World/Character/AnimationController.h"
#include"../World/Character/Animation.h"
#include"../Utility/Data.h"
#include"../Utility/ModelData.h"
namespace {
	const char* const kDataPath = "Data\\";
	const char* const kCsv = ".csv";
}
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
	class Resource {
	public:
		Resource() = default;
		~Resource() = default;
	public:
		int GetHandle() { return m_handle; }
		std::string GetName() { return m_name; }
	protected:
	void Reset();
	private:
		virtual void Load(std::string path)=0;
		virtual void Delete() = 0;
	protected:
		int m_handle;			// データのハンドル
		std::string m_name;	// データ名
	};

	
public:
	void End();
	static ResourceManager& GetInstance();
	/// <summary>
	/// グラフィックハンドルを取得する関数
	/// </summary>
	GraphData* GetGraph(std::string graphName);
	/// <summary>
	/// モデルハンドルのみを取得する関数
	/// </summary>
	int GetModel(std::string modelName,FileName modelType);
	
	ModelData GetModelCSV(std::string csvName);

private:

	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&)=delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;
private:
	std::vector<std::unique_ptr<GraphData>>m_graphData;
	std::vector <std::unique_ptr<ModelData>> m_modelData;
};

class ModelData:public ResourceManager::Resource {			// モデルのデータ
public:
	ModelData(std::string path);
	~ModelData();
private:
	void Load(std::string path)override;
	void Delete()override;
private:
	// アニメーションのハンドル
	std::vector<int> m_animHandle;
	// アニメーション管理
	AnimationController m_anim;
};
class GraphData:public ResourceManager::Resource {			// 画像のデータ
public:
	GraphData(std::string path);
	~GraphData();
private:
	void Load(std::string path)override;
	void Delete()override;
};