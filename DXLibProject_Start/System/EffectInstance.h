#pragma once
#include"pch.h"

#include"Utility/Vector3.h"
#include"World/Component/Transform.h"

class EffectResource;

/// <summary>
/// 再生中のエフェクトを管理するクラス
/// </summary>
class EffectInstance
{
private:
public:

	EffectInstance(std::shared_ptr<EffectResource> resource);
	virtual ~EffectInstance()=default;

	EffectInstance(const EffectInstance&) = delete;
	EffectInstance& operator= (const EffectInstance&) = delete;
	EffectInstance(EffectInstance&&) = delete;
	EffectInstance& operator= (const EffectInstance&&) = delete;

	bool play(const Vector3& position);
	void Update(float deltaTime);
	void Stop();
	/// <summary>
	/// 再生終了しているかどうかチェック
	/// </summary>
	/// <returns></returns>
	bool IsFnished()const;

	/// <summary>
	/// 再生するエフェクト素材
	/// </summary>
	std::shared_ptr<EffectResource>m_resource;
	/// <summary>
	/// 再生中のエフェクトハンドル
	/// </summary>
	int m_playHandle;
};

