#include"pch.h"

#include "EffectManager.h"
#include"EffectInstance.h"
#include"EffectResourceManager.h"
#include"EffectResource.h"

EffectManager& EffectManager::GetInstance()
{
    static EffectManager instance;
    return instance;
}
EffectManager::EffectManager()
{
    Init();
}

void EffectManager::Init()
{
    if (!m_pEffectResourceManager) {
        m_pEffectResourceManager = std::make_unique<EffectResourceManager>();
    }

    m_pEffectResourceManager->Init();
}

std::shared_ptr<EffectInstance> EffectManager::Play(int ID, const Transform* transform, float scale)
{
    // 再生するエフェクト素材を取得
    auto resource = m_pEffectResourceManager->GetResource(ID);
        // 素材がなければnullptr

    if (!resource)return nullptr;
    auto instance = std::make_shared<EffectInstance>(resource);
    // インスタンスの再生が失敗したら
    if (!instance)return nullptr;
    m_instances.emplace_back(instance);
    instance->Play(transform);
    instance->SetScale(scale);
    return instance;
}

void EffectManager::Update(float deltaTime)
{
    UpdateEffekseer3D(deltaTime);
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

void EffectManager::End()
{
    Clear();
}

void EffectManager::Clear()
{
    // すべてのエフェクト停止
    for (auto& instance : m_instances) {
        instance->Stop();
    }
}

int EffectManager::GetLoadedCound() const
{
    return m_pEffectResourceManager->GetLoadCount();
}

