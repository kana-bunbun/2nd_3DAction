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
private:

	StagePartDatabase& m_database;

};

