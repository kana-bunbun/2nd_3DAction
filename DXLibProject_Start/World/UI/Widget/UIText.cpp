#include"pch.h"
#include "UIText.h"


#include"../../../System/FontManager.h"
#include"../../../Utility/Color.h"

namespace {
	constexpr int kDefaultSize = 32;
	constexpr int kDefaultFontThickness = 3;
	const char* const kDefaultName = "Meiryo";
}

UIText::UIText() :
	m_text("text Unset"),
	isSelected(false),
	m_fontHandle(-1)
{
	m_param.normalColor = Color::kWhite;
	m_param.selectedColor = Color::kRed;
	m_param.fontName = kDefaultName;
	m_param.fontSize = kDefaultSize;
	m_param.thickness = kDefaultFontThickness;
}

UIText::UIText(const UITextParam& param):
	m_text("text Unset"),
	isSelected(false),
	m_param(param),
	m_fontHandle(-1)
{
}

UIText::UIText(const std::string & initText, const UITextParam & param) :
	m_text(initText),
	isSelected(false),
	m_param(param),
	m_fontHandle(-1)
{
}

UIText::UIText(const std::string& initText, const UITextParam& param, const Vector2& pos) :
	m_text(initText),
	isSelected(false),
	m_param(param),
	m_fontHandle(-1)
{
	SetPosition(pos);
	Build();
}

void UIText::OnInit()
{
	Build();
}

void UIText::OnUpdate(float deltaTime, const InputData& inputData)
{

}

void UIText::OnDraw()
{
	if (!m_visible)return;

	Vector2 worldPositon = GetWorldPosition();

	int color = (isSelected) ? m_param.selectedColor : m_param.normalColor;
	DrawStringToHandle(
		static_cast<int>(worldPositon.x),
		static_cast<int>(worldPositon.y),
		m_text.c_str(),color, m_fontHandle
	);

}

void UIText::OnEnd()
{

}

void UIText::Build()
{
	m_fontHandle = FontManager::GetInstance().GetFontHandle(m_param.fontName, m_param.fontSize, m_param.thickness);
}
