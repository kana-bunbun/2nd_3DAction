#include "SceneTextTest.h"
#include "../SceneSelectDebug.h"
#include"../Utility/Input.h"
#include"../Utility/Color.h"
#include"../Utility/MyMath.h"
#include"../Utility/Vector2.h"
#include"../../World/UI/Text/UIText.h"
#include"../../World/UI/TestScreen.h"

namespace {
	constexpr Vector2 kInitPos{ 400.0f,400.0f };
	const char* const kInitText = "Test AAA あ ｓ　 D";
	constexpr int kInitTextSize = 50;
	constexpr int kInitTextThickness = 8;

	constexpr int kFontNameMax = 10;
	const char* const kFontName[kFontNameMax] = {
		"Meiryo",
		"BIS UDPゴシック",
		"Gill Sans Ultra Bold",
		"Segoe MDL2 Assets",
		"MV Boil",
		"Marlett",
		"MS OutLook",
		"Segoe UI Emoji",
		"",
		"",
	};
}

SceneTextTest::SceneTextTest()
{
	m_textNameIndex = 0;
}

void SceneTextTest::Init()
{
	m_pScreen = std::make_unique<TestScreen>();
	m_pScreen->Init();

}

void SceneTextTest::End()
{

}

std::unique_ptr<SceneBase> SceneTextTest::Update(float deltaTime)
{
	if (Input::IsPressed(Input::Button::Back, Input::Pad::P1))
		return std::make_unique<SceneSelectDebug>();

	/*if (Input::IsPressed(Input::Button::X, Input::Pad::P1)) {
		m_textNameIndex--;
	m_textNameIndex = (kFontNameMax + m_textNameIndex) % kFontNameMax;
		m_pText->SetFontName(kFontName[m_textNameIndex]);
		m_pText->Build();
	}
	if (Input::IsPressed(Input::Button::Y, Input::Pad::P1)) {
		m_textNameIndex++;
	m_textNameIndex = (kFontNameMax + m_textNameIndex) % kFontNameMax;
		m_pText->SetFontName(kFontName[m_textNameIndex]);
		m_pText->Build();
	}*/
	if (Input::IsPressed(Input::Button::X, Input::Pad::P1)) {
		if (m_pScreen->GetState() == TestScreen::ScreenState::ModeSelect) {
			m_pScreen->SetScreenState(TestScreen::ScreenState::PressStay);
			m_pScreen->ShowPressStay();
		}

	}
	if (Input::IsPressed(Input::Button::Y, Input::Pad::P1)) {
		if (m_pScreen->GetState() == TestScreen::ScreenState::PressStay) {
		m_pScreen->SetScreenState(TestScreen::ScreenState::ModeSelect);
		m_pScreen->ShowModeSelect();
		}
	}
	m_pScreen->Update(deltaTime);

    return nullptr;
}

void SceneTextTest::Draw()
{
	DrawString(130, 130, "SceneTextTest", Color::kWhite);
	m_pScreen->Draw();
}
