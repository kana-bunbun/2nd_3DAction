#include "TestScreen.h"
#include"Text/UIText.h"
#include"../../Utility/Loder/CsvLoader.h"
namespace {
	const char* const kDataName = "TextUIParam";
	const char* const kInitText = "Tsgrrreat";
	constexpr Vector2 kInitPos{ 300.0f,400.0f };

	const char* const kLogoText = "Game Title";
	const char* const kPressText = "Press Button";
	const char* const kSelectStartText = "Game Start";
	const char* const kSelectOptionText = "Option";
	const char* const kSelectExitText = "Exit";
	constexpr Vector2 kLogoPos{ 350.0f,200.0f };
	constexpr Vector2 kPressPos{ 350.0f,450.0f };
	constexpr Vector2 kSelectStartPos{ 350.0f,400.0f };
	constexpr Vector2 kSelectOptionPos{ 350.0f,450.0f };
	constexpr Vector2 kSelectExitPos{ 350.0f,500.0f };
}
TestScreen::TestScreen():
	m_state(ScreenState::PressStay),
	m_pLogoText(nullptr),
	m_pPressText(nullptr),
	m_pSelectStartText(nullptr),
	m_pSelectOptionText(nullptr),
	m_pSelectExitText(nullptr)
{

}
void TestScreen::Init()
{
	// csvデータの読み込み
	auto data = Data::Csv::LoadCsvAs<UITextParam>(kDataName);

	// UIの登録
	m_pLogoText = CreateUIObject<UIText>(kLogoText, data[0], kLogoPos);
	m_pPressText = CreateUIObject<UIText>(kPressText, data[0], kPressPos);
	m_pSelectStartText = CreateUIObject<UIText>(kSelectStartText, data[0], kSelectStartPos);
	m_pSelectOptionText = CreateUIObject<UIText>(kSelectOptionText, data[0], kSelectOptionPos);
	m_pSelectExitText = CreateUIObject<UIText>(kSelectExitText, data[0], kSelectExitPos);

	m_pPressText->SetVisible(true);
	m_pSelectStartText->SetVisible(false);
	m_pSelectOptionText->SetVisible(false);
	m_pSelectExitText->SetVisible(false);

}

void TestScreen::ShowPressStay()
{
	m_pPressText->SetVisible(true);
	m_pSelectStartText->SetVisible(false);
	m_pSelectOptionText->SetVisible(false);
	m_pSelectExitText->SetVisible(false);

}

void TestScreen::ShowModeSelect()
{
	m_pPressText->SetVisible(false);
	m_pSelectStartText->SetVisible(true);
	m_pSelectOptionText->SetVisible(true);
	m_pSelectExitText->SetVisible(true);

}
