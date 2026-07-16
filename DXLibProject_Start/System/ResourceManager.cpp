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
		"Item\\",
		"Map\\",
		"Graph\\",
		"CSV\\",
	};
	const char* const kAnimation = "Animation\\";
	const char* const kPng = ".png";
	const char* const kMv1 = ".mv1";
	//const char* const kCsv = ".csv";
	// csvデータのパスが記されているインデックス(行)
	constexpr int kPathIndex = 1;
	// csvデータのモデルパスが記されているインデックス(列)
	constexpr int kModelIndex = 0;
	// データ読み込み時の不正値
	constexpr int kHandleInvalidValue = -1;
}

void ResourceManager::End()
{

}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;

}

GraphData* ResourceManager::GetGraph(std::string graphName)
{
	// 総当たりして同じ名前の画像を探す
	for (auto& graphData : m_graphData) {
		// 同じ名前のデータがあれば読み込み済みの判定
		if (graphData->GetName() != graphName)continue;
		return graphData.get();
	}

	// 以下の処理は読み込んでない判定としての処理
	//　パスの作成
	std::string path = kResourcePath;
	path += kFilePath[static_cast<int>(FileName::Graph)] + graphName + kPng;
	// グラフィックハンドルの読み込み
	std::unique_ptr<GraphData> graphData=std::make_unique<GraphData>(path);
	// 読み込み失敗したら不正値を返す
	if (graphData->GetHandle() == kHandleInvalidValue)return nullptr;

	// 以下の処理は読み込み成功時の処理
	// 配列に追加
	m_graphData.push_back(graphData);

	// グラフィックデータを返す
	return graphData.get();
}

int ResourceManager::GetModel(std::string modelName, FileName modelType)
{
	// 総当たりして同じ名前のデータを探す
	for (auto& model : m_modelData) {
		if (model->GetName() != modelName)continue;

		// モデルハンドルを複製して返す
		return MV1DuplicateModel(model->GetHandle());
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

ModelData ResourceManager::GetModelCSV(std::string csvName)
{
	// 総当たりして同じ名前のデータを探す
	for (auto& model : m_modelData) {
		if (model.modelName != csvName)continue;
		ModelData result = model;
		result.modelHandle = MV1DuplicateModel(model.modelHandle);
		// モデルハンドルを複製して渡す
		result.m_anim = model.m_anim.Duplicate();
		// モデルデータを返す
		return result;
	}

	// 以下の処理は読み込んでいない判定
	ModelData modelData;
	std::string path = kDataPath + csvName + kCsv;
	// csvパスを作成
	const auto& csvData = Data::Csv::LoadCsvAs<ModelPathParam>(path.c_str())[0];
	// モデルデータまでのパスを作成
	modelData.modelHandle = MV1LoadModel(csvData.modelPath.c_str());
	// 読み込みができていなければ処理しない
	if (modelData.modelHandle < 0)return modelData;
	for (int i = 0; i < csvData.animationPath.size() - 1; i++) {
		// アニメーションデータのパスを使って読み込み
		int animHandle = MV1LoadModel(csvData.animationPath[i].c_str());
		modelData.m_anim.AddAnim(animHandle);
	}
	// データに名前を付ける
	modelData.modelName = csvName;
	// 配列に追加
	m_modelData.push_back(modelData);

	return modelData;
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

void ModelData::Load(std::string path)
{

}

void ModelData::Delete()
{
	for (auto& anim : m_animHandle) {
		if (anim == kHandleInvalidValue)continue;
		MV1DeleteModel(anim);
		anim = kHandleInvalidValue;
}
	m_handle = kHandleInvalidValue;
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
	Reset();
}

void ResourceManager::Resource::Reset()
{
	m_handle = kHandleInvalidValue;
	m_name = "";
}
