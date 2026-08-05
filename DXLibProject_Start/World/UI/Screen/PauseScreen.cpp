#include "PauseScreen.h"
#include"../Widget/UIButton.h"
#include"../Widget/UIText.h"
#include"../Widget/UIImage.h"
#include"../Core/UIGroup.h"
#include"../../../System/ImageManager.h"
#include"../../../Utility/Loder/CsvLoader.h"
#include"../../../Utility/Game.h"
#include"../../../System/ResourceManager.h"
#include<memory>
namespace {
	const char* const kDataName = "TextUIParam";
	constexpr Vector2 kInitPos{ 300.0f,400.0f };
	const char* const kText = "Pause";
	const char* const kResumeText = "Resume";
	const char* const kExitText = "Exit";
	constexpr int kLogoPathID = 0;
	constexpr Vector2 kLogoPos{ 350.0f,200.0f };
	constexpr Vector2 kPressPos{ 350.0f,450.0f };
	constexpr Vector2 kSelectStartPos{ 0.0f,0.0f };
	constexpr Vector2 kSelectOptionPos{ 0.0f,50.0f };
	constexpr Vector2 kSelectExitPos{ 0.0f,100.0f };
	constexpr Vector2 kGroupPos{ 350.0f,400.0f };
}
PauseScreen::PauseScreen() :
	m_pButton(nullptr)
{

}

void PauseScreen::Init()
{
	auto data = Data::Csv::LoadCsvAs<UITextParam>(kDataName);
	auto frameHandle = ImageManager::GetInstance().GetImage(kLogoPathID);
	auto startText = std::make_unique <UIText>(kText, data[0], kInitPos);
	auto startImage = std::make_unique<UIImage>(frameHandle, kInitPos);
	m_pButton = CreateUIObject<UIButton>();
	m_pButton->SetPosition(kInitPos);
	m_pButton->AddChild(std::move(startImage));
	m_pButton->AddChild(std::move(startText));
	m_pGorupButtons = CreateUIObject<UIGroup>(kGroupPos);

	// pResumeButtonの登録・追加
	auto pResumeButton = std::make_unique<UIButton>();
	pResumeButton->SetPosition(kSelectStartPos);
	auto resumeText = std::make_unique <UIText>(kResumeText, data[0], kSelectStartPos);
	auto resumeImage = std::make_unique<UIImage>(frameHandle, kSelectStartPos);
	pResumeButton->AddChild(std::move(resumeText));
	pResumeButton->AddChild(std::move(resumeImage));
	pResumeButton->SetOnClick([this]() {
		m_result = ButtonResult::Resume;
		UIScreen::SetUICommand(UICommand::ResumeGame);
		});

	// pExitButtonの登録・追加
	auto pExitButton = std::make_unique<UIButton>();
	pExitButton->SetPosition(kSelectStartPos);
	auto exitText = std::make_unique <UIText>(kExitText, data[0], kSelectStartPos);
	auto exiImage = std::make_unique<UIImage>(frameHandle, kSelectStartPos);
	pExitButton->AddChild(std::move(exitText));
	pExitButton->AddChild(std::move(exiImage));
	pExitButton->SetOnClick([this]() {
		m_result = ButtonResult::Exit; 
		UIScreen::SetUICommand(UICommand::LoadDebugScene);
		});
	// Resumeボタンを選択肢に追加
	UIButton* pResume = pResumeButton.get();
	UIButton* pExit= pExitButton.get();
	m_selectButtons.emplace_back(pResume);
	m_selectButtons.emplace_back(pExit);
	m_pGorupButtons->AddChild(std::move(pResumeButton));
	m_pGorupButtons->AddChild(std::move(pExitButton));
}

void PauseScreen::Draw()
{
	// 画面全体を半透明で覆う
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color::kBlack, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	UIScreen::Draw();
}

void PauseScreen::Update(float deltaTime, const UIInput& input)
{
	if (input.key[static_cast<int>(UIInputState::Key::Up)][UIInputState::IsDown]) {
		SelectPrevButton();
	}
	if (input.key[static_cast<int>(UIInputState::Key::Down)][UIInputState::IsDown]) {
		SelectNextButton();
	}
	if (input.key[static_cast<int>(UIInputState::Key::Decide)][UIInputState::IsDown]) {
		ExecuteButton();
	}
	UIScreen::Update(deltaTime,input);
}

void PauseScreen::SelectNextButton()
{
	if (m_selectButtons.empty())return;
	m_selectIndex++;
	if (m_selectIndex >= m_selectButtons.size())m_selectIndex = 0;

}

void PauseScreen::SelectPrevButton()
{
	if (m_selectButtons.empty())return;
	m_selectIndex--;
	if (m_selectIndex < 0)m_selectIndex = m_selectButtons.size() - 1;
}

void PauseScreen::ExecuteButton()
{
	if (m_selectButtons.empty())return;
	m_selectButtons[m_selectIndex]->Execute();
}

PauseScreen::ButtonResult PauseScreen::ConsumeResult()
{
	auto result = m_result;
	m_result = PauseScreen::ButtonResult::None;
	return result;
}
