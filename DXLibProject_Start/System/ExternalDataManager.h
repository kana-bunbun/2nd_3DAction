#pragma once
#include"../Data/ModelPathParam.h"
#include"../World/GameObjectParam.h"
#include<array>
/// <summary>
/// 外部データの読み込み、情報の保持をする
/// </summary>
class ExternalDataManager
{
public:
	ExternalDataManager();
	~ExternalDataManager();

	void LoadAll();

	void Init();
	void End();

public:
	/// <summary>
	/// プレイヤーモデルのパス情報を取得
	/// </summary>
	ModelPathParam GetPlayerPath(int modelTpye) { return m_modelPathParam[modelTpye]; }
private:
	/// <summary>
	/// プレイヤーモデルのパス情報
	/// </summary>
	std::array <ModelPathParam , static_cast<int>(ModelName::Max) > m_modelPathParam;

};

