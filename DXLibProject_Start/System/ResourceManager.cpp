#include "ResourceManager.h"
#include "../Utility/Loder/CsvLoader.h"
#include "../World/Character/Animation.h"
#include<DxLib.h>



ResourceManager::~ResourceManager()
{
	End();
}

void ResourceManager::End()
{
	for (size_t i = 0; i < m_modelData.size(); i++) {
		if (!m_modelData[i])continue;
		delete m_modelData[i];
		m_modelData[i] = nullptr;
	}

	for (size_t i = 0; i < m_graphData.size(); i++) {
		if (!m_graphData[i])continue;
		delete m_graphData[i];
		m_graphData[i] = nullptr;
	}
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;

}

GraphData* ResourceManager::GetGraph(std::string dataName)
{
	// 総当たりして同じ名前の画像を探す
	for (auto& graphData : m_graphData) {
		// 同じ名前のデータがあれば読み込み済みの判定
		if (graphData->GetName() != dataName)continue;
		return graphData;
	}

	// 以下の処理は読み込んでない判定としての処理

	// グラフィックハンドルの読み込み
	GraphData* graphData = new GraphData(dataName);
	// 読み込み失敗したら不正値を返す
	if (graphData->GetHandle() == -1)return nullptr;
	// 以下の処理は読み込み成功時の処理
	// 配列に追加
	m_graphData.emplace_back(graphData);

	// グラフィックデータを返す
	return graphData;
}

ModelData* ResourceManager::GetModel(std::string dataName)
{
	// 総当たりして同じ名前のデータを探す
	for (auto& model : m_modelData) {
		if (model->GetName() != dataName)continue;
		m_DuplicateList.emplace_back(model->Duplicate());
		// モデルハンドルを複製して返す
		return m_DuplicateList[m_DuplicateList.size() - 1];
	}

	// 以下の処理は読み込んでいない判定
	// パスを作成
	// パスをもとにモデル読み込み
	ModelData* modelData = new ModelData(dataName);
	// 読み込み失敗していたら不正値を返す
	if (modelData->GetHandle() ==-1)return nullptr;

	// モデルハンドルを返す
	return modelData;
}
