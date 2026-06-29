#include "ResourceManager.h"
#include "../Utility/CsvLoader.h"
#include "../World/Character/Animation.h"
#include<DxLib.h>

namespace {
	const char* const kResourcePath = "Resource\\";
	const char* const kFilePath[static_cast<int>(ResourceManager::FileName::Max)] = {
		"Player\\",
		"Doragon\\",
		"Enemy\\",
		"Map\\",
		"Graph\\",
		"CSV\\",
	};
	const char* const kAnimation = "Animation\\";
	const char* const kPng = ".png";
	const char* const kMv1 = ".mv1";
	const char* const kCsv = ".csv";
	// csvデータのパスが記されているインデックス(行)
	constexpr int kPathIndex = 1;
	// csvデータのモデルパスが記されているインデックス(列)
	constexpr int kModelIndex = 0;
}

void ResourceManager::End()
{
	for (auto& graph : m_graphData) {
		DeleteGraph(graph.graphHandle);
		graph.graphHandle = -1;
		graph.graphName = "";
	}
	for (auto& modelData : m_modelData) {
		MV1DeleteModel(modelData.modelHandle);
		modelData.modelHandle = -1;
		modelData.anim.End();
		modelData.modelName = "";
	}
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;

}

int ResourceManager::GetGraph(std::string graphName)
{
	// 総当たりして同じ名前の画像を探す
	for (auto& graphData : m_graphData) {
		// 同じ名前のデータがあれば読み込み済みの判定
		if (graphData.graphName != graphName)continue;
		return graphData.graphHandle;
	}

	// 以下の処理は読み込んでない判定としての処理
	//　パスの作成
	std::string path = kResourcePath;
	path += kFilePath[static_cast<int>(FileName::Graph)] + graphName + kPng;
	GraphData graphData;
	// グラフィックハンドルの読み込み
	graphData.graphHandle = LoadGraph(path.c_str());
	// データに名前を付ける
	graphData.graphName = graphName;
	// 読み込み失敗したら不正値を返す
	if (graphData.graphHandle < 0)return -1;

	// 以下の処理は読み込み成功時の処理
	// 配列に追加
	m_graphData.push_back(graphData);

	// グラフィックハンドルを返す
	return graphData.graphHandle;
}

int ResourceManager::GetModel(std::string modelName, FileName modelType)
{
	// 総当たりして同じ名前のデータを探す
	for (auto& model : m_modelData) {
		if (model.modelName != modelName)continue;

		// モデルハンドルを複製して返す
		return MV1DuplicateModel(model.modelHandle);
	}

	// 以下の処理は読み込んでいない判定
	// パスを作成
	std::string path = kResourcePath;
	path += kFilePath[static_cast<int>(modelType)] + modelName + kMv1;
	// パスをもとにモデル読み込み
	ModelData modelData;
	modelData.modelHandle = MV1LoadModel(path.c_str());
	// 読み込み失敗していたら不正値を返す
	if (modelData.modelHandle < 0)return -1;
	modelData.modelName = modelName;

	// モデルハンドルを返す
	return modelData.modelHandle;
}

ResourceManager::ModelData ResourceManager::GetModelCSV(std::string csvName)
{
	// 総当たりして同じ名前のデータを探す
	for (auto& model : m_modelData) {
		if (model.modelName != csvName)continue;
		ModelData result = model;
		result.modelHandle = MV1DuplicateModel(model.modelHandle);
		// モデルハンドルを複製して渡す
		result.anim=model.anim.Duplicate();
		// モデルデータを返す
		return result;
	}

	// 以下の処理は読み込んでいない判定

	// csvパスを作成
	std::string path = kResourcePath;
	path += kFilePath[static_cast<int>(ResourceManager::FileName::CSV)] + csvName + kCsv;
	CsvLoader csvData = CsvLoader(path);
	// モデルデータまでのパスを作成
	std::string dataPath = kResourcePath;
	ModelData modelData;
	modelData.modelHandle = MV1LoadModel((dataPath + csvData.GetLoadData()[kPathIndex][kModelIndex]+kMv1).c_str());
	// 読み込みができていなければ処理しない
	if (modelData.modelHandle < 0)return modelData;
	// アニメーションデータまでのパスを作成
	dataPath += kAnimation;
	for (int i = 0; i < csvData.GetLoadData()[0].size()-1; i++) {
		// アニメーションデータのパスを使って読み込み
		int animIndex = i + 1;
		int animHandle = MV1LoadModel((dataPath + csvData.GetLoadData()[kPathIndex][animIndex] + kMv1).c_str());
		modelData.anim.AddAnim(animHandle);
	}
	// データに名前を付ける
	modelData.modelName = csvName;
	// 配列に追加
	m_modelData.push_back(modelData);

	return modelData;
}
