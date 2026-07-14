#pragma once
#include<string>
#include<vector>
#include"../World/Character/AnimationController.h"
#include"../World/Character/Animation.h"
#include"../Utility/Data.h"
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
	template<typename T>
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

template<typename T>
inline ResourceManager::ModelData ResourceManager::GetModelCSV(std::string csvName)
{
	// 総当たりして同じ名前のデータを探す
	for (auto& model : m_modelData) {
		if (model.modelName != csvName)continue;
		ModelData result = model;
		result.modelHandle = MV1DuplicateModel(model.modelHandle);
		// モデルハンドルを複製して渡す
		result.anim = model.anim.Duplicate();
		// モデルデータを返す
		return result;
	}

	// 以下の処理は読み込んでいない判定

	// csvパスを作成
	const auto& csvData = Data::Csv::LoadCsvAs<T>(path)[0];
	// モデルデータまでのパスを作成
	modelData.modelHandle = MV1LoadModel(csvData.modelPath).c_str());
	// 読み込みができていなければ処理しない
	if (modelData.modelHandle < 0)return modelData;
	for (int i = 0; i < csvData.GetLoadData()[0].size() - 1; i++) {
		// アニメーションデータのパスを使って読み込み
		int animIndex = i + 1;
		int animHandle = MV1LoadModel(csvData.animPath[i]).c_str());
		modelData.anim.AddAnim(animHandle);
	}
	// データに名前を付ける
	modelData.modelName = csvName;
	// 配列に追加
	m_modelData.push_back(modelData);

	return modelData;
}
