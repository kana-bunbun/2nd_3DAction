#include "TestScreen.h"
#include"../Text/UIText.h"
#include"../Image/UIImage.h"
#include"../UIButton.h"
#include"../Image/ImageManager.h"
#include"../UIGroup.h"
#include"../../../Utility/Loder/CsvLoader.h"
namespace {
	const char* const kDataName = "TextUIParam";
	const char* const kInitText = "Tsgrrreat";
	constexpr Vector2 kInitPos{ 300.0f,400.0f };

	const char* const kLogoText = "Game Title";
	const char* const kPressText = "Press Button";
	const char* const kSelectStartText = "Game Start";
	const char* const kSelectOptionText = "Option";
	const char* const kSelectExitText = "Exit";
	const char* const kLogoPath = "Resource\\Test\\GameLogo.png";
	const char* const kFramePath = "Resource\\Test\\frameImage.png";
	constexpr Vector2 kLogoPos{ 350.0f,200.0f };
	constexpr Vector2 kPressPos{ 350.0f,450.0f };
	constexpr Vector2 kSelectStartPos{ 0.0f,0.0f };
	constexpr Vector2 kSelectOptionPos{ 0.0f,50.0f };
	constexpr Vector2 kSelectExitPos{ 0.0f,100.0f };
	constexpr Vector2 kGroupPos{ 350.0f,400.0f };
}
TestScreen::TestScreen():
	m_state(ScreenState::PressStay),
	m_pPressText(nullptr),
	m_pLogoImage(nullptr),
	m_pGorupText(nullptr),
	m_selectIndex(0),
	m_result(TestScreen::ButtonResult::None)
{

}
void TestScreen::Init()
{
	// csvデータの読み込み
	auto data = Data::Csv::LoadCsvAs<UITextParam>(kDataName);

	// UIの登録
	m_pPressText = CreateUIObject<UIText>(kPressText, data[0], kPressPos);
	int handle = ImageManager::GetInstance().GetGraphHandle(kLogoPath);
	int frameHandle = ImageManager::GetInstance().GetGraphHandle(kFramePath);
	m_pLogoImage = CreateUIObject<UIImage>(handle, kLogoPos);
	m_pGorupText = CreateUIObject<UIGroup>(kGroupPos);

	m_pPressText->SetVisible(true);
	m_pGorupText->SetVisible(true);

	/*auto startText = std::make_unique<UIText>(kSelectStartText, data[0], kSelectStartPos);
	auto optionText = std::make_unique<UIText>(kSelectOptionText, data[0], kSelectOptionPos);
	auto exitText = std::make_unique<UIText>(kSelectExitText, data[0], kSelectExitPos);

	m_pGorupText->AddChild(std::move(startText));
	m_pGorupText->AddChild(std::move(optionText));
	m_pGorupText->AddChild(std::move(exitText));*/

	// StartButtonの登録・追加
	auto startButton = std::make_unique<UIButton>();
	startButton->SetPosition(kSelectStartPos);
	auto startText = std::make_unique <UIText>(kSelectStartText, data[0], kSelectStartPos);
	auto startImage = std::make_unique<UIImage>(frameHandle, kSelectStartPos);
	startButton->AddChild(std::move(startImage));
	startButton->AddChild(std::move(startText));

	startButton->SetOnClick(
		[this]() {
		printfDx("GameStart\GameStart\GameStart\GameStart\GameStart\n"); 
			m_result = ButtonResult::Start; 
			}
	);
	UIButton* pStartButton = startButton.get();
	m_selectButtons.emplace_back(pStartButton);

	m_pGorupText->AddChild(std::move(startButton));
	auto optionButton = std::make_unique<UIButton>();
	optionButton->SetPosition(kSelectOptionPos);
	auto optionText = std::make_unique <UIText>(kSelectOptionText, data[0], kSelectOptionPos);
	auto optionImage = std::make_unique<UIImage>(frameHandle, kSelectOptionPos);
	optionButton->AddChild(std::move(optionImage));
	optionButton->AddChild(std::move(optionText));
	optionButton->SetOnClick(
		[this]() {
			printfDx("Option\Option\Option\Option\Option\n");
	m_result = ButtonResult::Option; }
	);
	UIButton* pOptionButton = optionButton.get();
	m_selectButtons.emplace_back(pOptionButton);
	m_pGorupText->AddChild(std::move(optionButton));
	auto exitButton = std::make_unique<UIButton>();
	exitButton->SetPosition(kSelectExitPos);
	auto exitText = std::make_unique <UIText>(kSelectExitText, data[0], kSelectExitPos);
	auto exitImage = std::make_unique<UIImage>(frameHandle, kSelectExitPos);
	exitButton->AddChild(std::move(exitImage));
	exitButton->AddChild(std::move(exitText));
	exitButton->SetOnClick(
		[this]() {
			printfDx("Exit\Exit\Exit\Exit\Exit\n");
			m_result = ButtonResult::Exit; 
		}
	);

	UIButton* pExitButton = exitButton.get();
	m_selectButtons.emplace_back(pExitButton);
	m_pGorupText->AddChild(std::move(exitButton));
}

void TestScreen::ShowPressStay()
{
	m_pPressText->SetVisible(true);
	m_pGorupText->SetVisible(false);
}

void TestScreen::ShowModeSelect()
{
	m_pPressText->SetVisible(false);
	m_pGorupText->SetVisible(true);
}

void TestScreen::SelectNextButton()
{
	if (m_selectButtons.empty())return;
	m_selectIndex++;
	if (m_selectIndex >=m_selectButtons.size())m_selectIndex = 0;

}

void TestScreen::SelectPrevButton()
{
	if (m_selectButtons.empty())return;
	m_selectIndex--;
	if (m_selectIndex < 0)m_selectIndex = m_selectButtons.size() - 1;
}

void TestScreen::ExecuteButton()
{
	if (m_selectButtons.empty())return;
	m_selectButtons[m_selectIndex]->Execute();
}

TestScreen::ButtonResult TestScreen::ConsumeResult()
{
	auto result = m_result;
	m_result = TestScreen::ButtonResult::None;
	return result;
}
