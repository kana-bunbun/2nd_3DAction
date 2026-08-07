#pragma once
#include<string>
class EffectResource
{
public:
	EffectResource(int ID,int handle);
	~EffectResource();

	// 素材をコピーされることを防ぐ
	EffectResource(const EffectResource&) = delete;
	EffectResource& operator=(const EffectResource&) = delete;
	EffectResource(EffectResource&&) = delete;
	EffectResource& operator=(const EffectResource&&) = delete;

	bool Load();
	bool IsLoaded()const { return m_handle != -1; }
	int GetHandle()const { return m_handle; }
	int GetID()const { return ID; }
public:
	int ID;
	/// <summary>
	/// エフェクトハンドル
	/// </summary>
	int m_handle;
};

