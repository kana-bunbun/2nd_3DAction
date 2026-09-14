#include "pch.h"
#include "StageSpawner.h"
#include"System/ResourceManager.h"
#include"Stage/StagePartDatabase.h"
#include"Stage/PartData.h"
#include "World/Object/StagePart.h"
#include "World/GameObjectManager.h"
#include"System/CollisionDataManager.h"

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
    // 生成したStagePartにパラメータ設定
    SetUpStagePart(*part, *pData, partName);

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

StagePart* StageSpawner::AddStagePart(const std::string& partName)
{

    // DatabaseからStageのPartを取得
    const Stage::PartData* pData = m_database.GetData(partName);

    // データの確認
    // ヒューマンエラーを防ぐ
    assert(pData);

    // StagePartのインスタンスを生成
    auto part = GameObjectManager::GetInstance().CreateObject<StagePart>();
    // 生成したStagePartにパラメータ設定
    SetUpStagePart(*part, *pData, partName);

    return part;
}

void StageSpawner::AddStageData(const Stage::StageData& stageData)
{
    // StageDataの中に登録されているobjectをGameObjectManagerに登録する
    for (const auto& objectData : stageData.objects) {
        auto* part = AddStagePart(objectData.partName);

        // 登録したらTransform設定
        part->SetTransform(objectData.transform);
    }

}

void StageSpawner::SetUpStagePart(StagePart& part, const Stage::PartData& data, const std::string& partName)
{
    // パーツの名前設定
    part.SetName(partName);

    // モデルの設定
    auto model = ResourceManager::GetInstance().GetModel(data.modelName);
    part.SetModelData(std::move(model));
    CollisionParam _collisionParam=CollisionDataManager::GetInstance().GetCollisionData(data.CollisionParamID);
    // コリジョンの設定
    if (data.hasCollision) {
        part.AddCollision(_collisionParam);
    }
}