#pragma once
#include<string>
#include"Data/EffectPathParam.h"
class EffectResource
{
public:
	EffectResource(const EffectPathParam& param);
	~EffectResource();

	// 素材をコピーされることを防ぐ
	EffectResource(const EffectResource&) = delete;
	EffectResource& operator=(const EffectResource&) = delete;
	EffectResource(EffectResource&&) = delete;
	EffectResource& operator=(const EffectResource&&) = delete;

	bool Load();
	bool IsLoaded()const { return m_handle != -1; }
	int GetHandle()const { return m_handle; }
	int GetID()const { return m_ID; }
	bool GetIsChace()const { return m_isChace; }
public:
	int m_ID;
	/// <summary>
	/// エフェクトのパラメータ
	/// </summary>
	EffectPathParam m_param;
	/// <summary>
	/// エフェクトハンドル
	/// </summary>
	int m_handle;
	/// <summary>
	/// 生成時に指定されたトランスフォームを追従するかどうか
	/// </summary>
	bool m_isChace;
};

