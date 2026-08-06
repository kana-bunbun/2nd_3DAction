#include "UIItemCursor.h"
#include"../../../System/ImageManager.h"
#include"../../../Utility/Game.h"
#include"../../../Utility/MyMath.h"

namespace {
	constexpr int kCursorGraphPathID = 1501;
	constexpr float kCursorGraphScale = 1.3f * Game::kWindowScale;
	constexpr float kLerpTime = 1.0f/0.2f;
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
	Vector2 differ = m_desirePosition - m_position;
	float sqLength = differ.GetSqLength();
	if (sqLength < MyMath::SquareEpsilon) {
		m_position = m_desirePosition;
		return;
	}

	float lerpSpeed = deltaTime * kLerpTime;
	Vector2 lerp = differ * MyMath::Clamp(lerpSpeed,0.0f,1.0f);
	m_position += lerp;
}

void UIItemCursor::OnDraw()
{
	if (m_image->GetHandle() == -1)return;
	DrawRotaGraph(m_position.x, m_position.y, kCursorGraphScale, 0, m_image->GetHandle(), TRUE);
}
