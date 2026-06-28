#include "BillboardManager.h"
#include<DxLib.h>
namespace {
	const char* const kGraphPath[BillboardManager::eBillboard::Max] = {
		"Resource\\Graph\\BillboardText_Stair.png",
	};
}
BillboardManager& BillboardManager::GetInstance()
{

	static BillboardManager instance;
	return instance;
}

BillboardManager::~BillboardManager()
{
	for (int& graphHandle : m_graphHandles) {
		DeleteGraph(graphHandle);
		graphHandle = -1;
	}
}

void BillboardManager::Init()
{
	for (int i = 0; i < m_graphHandles.size();i++) {
		m_graphHandles[i] = LoadGraph(kGraphPath[i]);
	}
}

void BillboardManager::End()
{}

void BillboardManager::DrawBillboard(Vector3 position, float centerX, float centerY, float size, float radian, eBillboard billboardType)
{
	if (m_graphHandles[billboardType] == -1)return;
	DrawBillboard3D(position.ToVECTOR(), centerX, centerY, size, radian, m_graphHandles[billboardType], TRUE);
}