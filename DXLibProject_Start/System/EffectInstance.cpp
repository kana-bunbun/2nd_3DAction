#include "EffectInstance.h"
#include<cassert>
#include<EffekseerForDXLib.h>
#include"System/EffectResource.h"
EffectInstance::EffectInstance(std::shared_ptr<EffectResource> resource):
	m_resource(resource),
	m_playHandle(-1)
{
	// 万が一Resoueceがnulptrの時警告
	assert(resource && "EffectInstance not get");
}

bool EffectInstance::play(const Vector3& position)
{
	// 二重再生禁止

	// エフェクト再生
	m_playHandle = PlayEffekseer3DEffect(m_resource->GetHandle());

	// 取得できなければreturn
	if (m_playHandle == -1)return false;

	// エフェクトの座標を設定
	SetPosPlayingEffekseer3DEffect(m_playHandle, position.x, position.y, position.z);

	return true;
}
void EffectInstance::Update(float deltaTime) {

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
