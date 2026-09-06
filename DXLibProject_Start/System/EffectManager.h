#pragma once
#include"pch.h"
#include"Utility/Vector3.h"
class EffectInstance;
class EffectResourceManager;

/// <summary>
/// エフェクトの使用状況を管理するクラス
/// 読み込み関連はEffectResourceManagerクラスが担う
/// </summary>
class EffectManager
{
public:

	EffectManager() = default;
	EffectManager(EffectResourceManager& resourceManager);
	std::shared_ptr<EffectInstance>Play(int Id, const Vector3& pos);

	void Update(float deltaTime);
	void Draw();

	void Clear();

	int GetInstanceCount()const { return m_instances.size(); }


private:

	/// <summary>
	/// 読み込み担当のEffectResourceManagerの参照
	/// このクラスでは「絶対」に使用するので参照で持つ
	/// 注意点としては、後から差し替えることが面倒・依存度が上がる
	/// </summary>
	EffectResourceManager& m_effectResoruceManager;

	/// <summary>
	/// 管理しているインスタンス
	/// </summary>
	std::vector<std::shared_ptr<EffectInstance>>m_instances;

};

