#include "UIImage.h"

UIImage::UIImage():
	m_graphHandle(-1)
{

}

UIImage::UIImage(int handle, const Vector2 & position):
	m_graphHandle(handle)
{
	SetPosition(position);
}

void UIImage::OnInit()
{

}

void UIImage::OnUpdate(float deltaTime)
{

}

void UIImage::OnDraw()
{
	if (!m_visible)return;

	Vector2 worldPositon = GetWorldPosition();

	DrawGraph(
		static_cast<int>(worldPositon.x),
		static_cast<int>(worldPositon.y),
		m_graphHandle,TRUE
	);
}

void UIImage::OnEnd()
{

}
