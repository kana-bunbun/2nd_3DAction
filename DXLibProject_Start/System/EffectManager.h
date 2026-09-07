#pragma once
#include"pch.h"
#include"World/Component/Transform.h"
class EffectInstance;
class EffectResourceManager;

/// <summary>
/// エフェクトの使用状況を管理するクラス
/// 読み込み関連はEffectResourceManagerクラスが担う
/// </summary>
class EffectManager
{
public:
	static EffectManager& GetInstance();
	void Init(EffectResourceManager& resourceManager);
	std::shared_ptr<EffectInstance>Play(int Id, const Transform* pos);
	void Update(float deltaTime);
	void Draw();

	void Clear();

	int GetInstanceCount()const { return m_instances.size(); }


private:
	EffectManager() = default;
	EffectManager& operator=(const EffectManager&) = delete;
	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(EffectManager&&) = delete;
	EffectManager(const EffectManager&&) = delete;
private:

	/// <summary>
	/// 読み込み担当のEffectResourceManagerの参照
	/// このクラスでは絶対に使用するので参照で持つ
	/// 注意点としては、後から差し替えることが面倒・依存度が上がる
	/// </summary>
	EffectResourceManager& m_effectResoruceManager;

	/// <summary>
	/// 管理しているインスタンス
	/// </summary>
	std::vector<std::shared_ptr<EffectInstance>>m_instances;

};

