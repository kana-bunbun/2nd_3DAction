#include"pch.h"
#include "EFfectResource.h"
#include"EffectResourceManager.h"
EffectResource::EffectResource(int ID,int handle,bool isChace):
	ID(ID),m_handle(handle),m_isChace(isChace)
{
}

EffectResource::~EffectResource()
{
	DeleteEffekseerEffect(m_handle);
}
bool EffectResource:: Load() {
	if (IsLoaded()) return false;
	return true;
}
