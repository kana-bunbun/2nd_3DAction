#pragma once
#include"../Data/ModelPathParam.h"
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
	ModelPathParam GetPlayerPath() { return m_playerPathParam; }
private:
	/// <summary>
	/// プレイヤーモデルのパス情報
	/// </summary>
	ModelPathParam m_playerPathParam;

};

