#pragma once
#include"pch.h"
#include"StageData.h"

class StagePart;
class StagePartDatabase;
class ResourceManager;

class StageSpawner
{

public:

	StageSpawner(StagePartDatabase& database);

	std::unique_ptr<StagePart>Spawn(const std::string& partName);

	std::vector<std::unique_ptr<StagePart>>SpawnStage(const Stage::StageData& stageData);
	/// <summary>
	/// ステージオブジェクトを1つ生成してGameObjectManagerに登録
	/// </summary>
	/// <returns></returns>
	StagePart* AddStagePart(const std::string& partName);
private:

	StagePartDatabase& m_database;

};

