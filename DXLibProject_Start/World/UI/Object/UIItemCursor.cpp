#include "UIItemCursor.h"
#include"../../../System/ImageManager.h"
#include"../../../Utility/Game.h"

namespace {
	constexpr int kCursorGraphPathID = 1501;
	constexpr float kCursorGraphScale = 1.3f * Game::kWindowScale;
	
}

UIItemCursor::UIItemCursor()
{
	m_image = ImageManager::GetInstance().GetImage(kCursorGraphPathID);
}

void UIItemCursor::OnInit()
{

}

void UIItemCursor::OnEnd()
{

}

void UIItemCursor::OnUpdatate(float deltaTime)
{

}

void UIItemCursor::OnDraw()
{
	if (m_image->GetHandle() == -1)return;
	DrawRotaGraph(m_position.x, m_position.y, kCursorGraphScale, 0, m_image->GetHandle(), TRUE);
}
