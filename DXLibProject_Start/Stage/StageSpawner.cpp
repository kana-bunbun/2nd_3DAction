#include "pch.h"
#include "StageSpawner.h"
#include"System/ResourceManager.h"
#include"Stage/StagePartDatabase.h"
#include"Stage/PartData.h"
#include "World/Object/StagePart.h"

StageSpawner::StageSpawner(StagePartDatabase& database):
    m_database(database)
{}

std::unique_ptr<StagePart> StageSpawner::Spawn(const std::string & partName)
{
    // DatabaseからStageのPartを取得
    const Stage::PartData* pData = m_database.GetData(partName);

    // データの確認
    // ヒューマンエラーを防ぐ
    assert(pData);

    // StagePartのインスタンスを生成
    auto part = std::make_unique<StagePart>();
    // インスタンスをモデルに設定
    auto model = ResourceManager::GetInstance().GetModel(pData->modelName);
    part->SetModelData(std::move(model));
    // インスタンスにコリジョンの設定
    if (pData->hasCollision) {

    }


    return part;
}

std::vector<std::unique_ptr<StagePart>> StageSpawner::SpawnStage(const Stage::StageData& stageData)
{
    // 生成結果を用意
    std::vector<std::unique_ptr<StagePart>>result;

    // 引数から要素数を確保
    result.reserve(stageData.objects.size());

    for (const auto& objectData : stageData.objects) {

        // パーツの生成
        auto part = Spawn(objectData.partName);

        // Transformの設定
        part->SetTransform(objectData.transform);

        // 配列に追加
        result.emplace_back(std::move(part));

    }
    return result;
}
