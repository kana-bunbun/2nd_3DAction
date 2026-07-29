#include "TitleLogo.h"
#include<DxLib.h>
#include"../../Utility/Color.h"
namespace {
	const char* const kInitText="testtt";
}
TitleLogo::TitleLogo():
	m_text(kInitText)
{

}

void TitleLogo::OnInit()
{}

void TitleLogo::OnEnd()
{}

void TitleLogo::OnUpdate(float deltaTime)
{

}

void TitleLogo::OnDraw()
{
	if (!m_visible)return;

	DrawString(
		static_cast<int>(m_position.x),
		static_cast<int>(m_position.y),
		m_text.c_str(),
		Color::kGreen
	);

}
