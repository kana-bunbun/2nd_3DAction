#pragma once
#include"pch.h"
#include"PartData.h"

class StagePartDatabase
{
public:

	/// <summary>
	/// データベースにStageのPartDataを登録
	/// </summary>
	/// <param name="partName"></param>
	/// <param name="data"></param>
	void Register(const std::string& partName, const Stage::PartData& data);


	/// <summary>
	/// データベースに登録しているパーツを取得
	/// </summary>
	/// <param name="partName"></param>
	/// <returns></returns>
	const Stage::PartData* GetData(const std::string& partName)const;
private:
	/// <summary>
	/// ステージデータの一覧
	/// </summary>
	std::unordered_map < std::string, Stage::PartData >m_stagePartDatabase;
};

