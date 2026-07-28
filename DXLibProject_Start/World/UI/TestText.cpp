#include "TestText.h"
#include "../../Utility/Color.h"
namespace {
	const char* const kInitText = "asg";
	constexpr float kBlinkSpeed = 5.0f;
}
TestText::TestText():
	m_text(kInitText),
	m_blinkTimer(0.0f)
{

}

void TestText::Init()
{}

void TestText::Update(float deltaTime)
{
	m_blinkTimer += deltaTime;
	if (sinf(m_blinkTimer * kBlinkSpeed) > 0.0f) {
		m_visible = true;
	}
	else {
		m_visible = false;
	}

}

void TestText::Draw()
{
	if (!m_visible)return;
	DrawString(
		static_cast<int>(m_position.x),
		static_cast<int>(m_position.y),
		m_text.c_str(),
		Color::kGreen
	);
}

void TestText::End()
{}
