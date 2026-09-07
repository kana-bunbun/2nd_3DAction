#include"pch.h"
#include "EffectInstance.h"
#include"System/EffectResource.h"
EffectInstance::EffectInstance(std::shared_ptr<EffectResource> resource):
	m_resource(resource),
	m_playHandle(-1)
{
	// 万が一Resoueceがnulptrの時警告
	assert(resource && "EffectInstance not get");
}

bool EffectInstance::Play(const Transform* transform)
{
	// 二重再生禁止
	// エフェクト再生
	m_playHandle = PlayEffekseer3DEffect(m_resource->GetHandle());

	// 取得できなければreturn
	if (m_playHandle == -1)return false;
	// トランスフォームの設定
	m_transform = transform;
	// エフェクトの座標を設定
	SetPosPlayingEffekseer3DEffect(m_playHandle, transform->position.x, transform->position.y, transform->position.z);

	return true;
}
void EffectInstance::Update(float deltaTime) {

	if (!m_resource->GetIsChace()) return;
	SetPosPlayingEffekseer3DEffect(m_playHandle, m_transform->position.x, m_transform->position.y, m_transform->position.z);
	SetRotationPlayingEffekseer3DEffect(m_playHandle, m_transform->rotation.x, m_transform->rotation.y, m_transform->rotation.z);

}
void EffectInstance::Stop()
{
	//取得できていなければreturn
	if (m_playHandle == -1)return;
	StopEffekseer3DEffect(m_playHandle);
	m_playHandle = -1;
}

bool EffectInstance::IsFnished() const
{
	if (m_playHandle == -1)return true;
	return IsEffekseer3DEffectPlaying(m_playHandle);
}
