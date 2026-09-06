#include"pch.h"
#include "EFfectResource.h"
#include"EffectResourceManager.h"
EffectResource::EffectResource(int ID,int handle):
	ID(ID),m_handle(handle)
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
