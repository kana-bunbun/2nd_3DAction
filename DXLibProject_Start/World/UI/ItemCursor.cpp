#include "ItemCursor.h"
#include"../../Utility/Game.h"
#include"../../Utility/Vector3.h"
namespace {

	// スロット表示する際の中心座標
	constexpr Vector3 kSlotCenterPos = { Game::kScreenWidth /  3.0f,Game::kScreenHeight * 0.9f,0.0f };
	// スロットのスケール
	constexpr float kSlotScale = 0.05f;
	constexpr float kSlotDistance = 100.0f * Game::kWindowScale;

	const char* const kBackGroundPath = "Resource\\UI\\Icon Background.png";
}
ItemCursor::ItemCursor()
{
	m_backGroundHandle = LoadGraph(kBackGroundPath);
}

ItemCursor::~ItemCursor()
{
	DeleteGraph(m_backGroundHandle);
	m_backGroundHandle = -1;
}

void ItemCursor::Init()
{

}

void ItemCursor::End()
{

}

void ItemCursor::Update(float deltaTime)
{

}

void ItemCursor::Draw()
{
	for (int i = 0; i < kSlotNum;i++) {
		float posX = kSlotCenterPos.x + (kSlotDistance * (-kSlotNum * 0.5f + i+0.5f));
		DrawRotaGraph(posX, kSlotCenterPos.y, kSlotScale, 0, m_backGroundHandle, TRUE);
	}
}
