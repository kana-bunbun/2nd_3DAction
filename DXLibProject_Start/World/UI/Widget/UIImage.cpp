#include"pch.h"
#include "UIImage.h"
#include"../../../System/ImageResource.h"
UIImage::UIImage():
	m_image(nullptr)
{

}


UIImage::UIImage(std::shared_ptr<ImageResource> image, const Vector2& position):
	m_image(image)
{
	SetPosition(position);
}

void UIImage::OnInit()
{

}

void UIImage::OnUpdate(float deltaTime, const InputData& inputData)
{

}

void UIImage::OnDraw()
{
	if (!m_visible)return;

	Vector2 worldPositon = GetWorldPosition();

	DrawGraph(
		static_cast<int>(worldPositon.x),
		static_cast<int>(worldPositon.y),
		m_image->GetHandle(), TRUE
	);
}

void UIImage::OnEnd()
{

}
