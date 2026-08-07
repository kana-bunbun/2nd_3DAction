#include "EffectManager.h"
#include"EffectInstance.h"
#include"EffectResourceManager.h"
#include"EffectResource.h"
#include<EffekseerForDXLib.h>
EffectManager::EffectManager(EffectResourceManager& resourceManager):
    m_effectResoruceManager(resourceManager)
{}

std::shared_ptr<EffectInstance> EffectManager::Play(int ID, const Vector3 & pos)
{
    // 再生するエフェクト素材を取得
    auto resource = m_effectResoruceManager.GetResource(ID);
        // 素材がなければnullptr

    if (!resource)return nullptr;
    auto instance = std::make_shared<EffectInstance>(resource);
    // インスタンスの再生が失敗したら
    if (!instance)return nullptr;
    m_instances.emplace_back(instance);

    return instance;
}

void EffectManager::Update(float deltaTime)
{
    UpdateEffekseer3D();
    for (auto& instance : m_instances) {
        instance->Update(deltaTime);
    }
    std::erase_if(
        m_instances,
        [](const auto& instance) {
            return instance->IsFnished();
        });

}

void EffectManager::Draw()
{
    DrawEffekseer3D();
}

void EffectManager::Clear()
{
    // すべてのエフェクト停止
    for (auto& instance : m_instances) {
        instance->Stop();
    }
}
