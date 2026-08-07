#include "EFfectResource.h"
#include<EffekseerForDXLib.h>
#include"EffectResourceManager.h"
EffectResource::EffectResource(int ID,int handle):
	ID(ID),m_handle(handle)
{
}

EffectResource::~EffectResource()
{
}
bool EffectResource:: Load() {
	//m_handle=LoadEffekseerEffect()
	if (m_handle == -1) return false;
	return true;
}
