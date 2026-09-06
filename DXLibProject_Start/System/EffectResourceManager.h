#pragma once
#include"pch.h"

class EffectResource;
class EffectPathParam;

class EffectResourceManager
{
public:

	EffectResourceManager();
	~EffectResourceManager();

	/// <summary>
	/// エフェクトの読み込み
	/// </summary>
	/// <param name="ID"></param>
	/// <returns></returns>
	bool LoadEffect(int ID);
	/// <summary>
	/// エフェクト素材の取得
	/// </summary>
	std::shared_ptr<EffectResource> GetResource(int ID)const;
	const EffectPathParam& GetEffectParam(int ID);
	/// <summary>
	/// 管理しているエフェクトの数を取得
	/// </summary>
	/// <returns></returns>
	int GetLoadCount()const { return static_cast<int>(m_resources.size()); }
	void Clear() { m_resources.clear(); }
private:
	std::unordered_map < int, std::shared_ptr<EffectResource> >m_resources;
	std::vector<EffectPathParam>m_effectPathParam;
};

