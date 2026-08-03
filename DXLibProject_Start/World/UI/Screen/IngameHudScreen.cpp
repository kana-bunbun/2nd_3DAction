#include "IngameHudScreen.h"
#include"../../../Utility/Loder/CsvLoader.h"
#include"../../../Data/UITextParam.h"
#include"../Widget/UIText.h"
#include"../Widget/UIImage.h"
#include"../../../System/ImageManager.h"
#include"../Widget/UIButton.h"
namespace {
	const char* const kDataName = "TextUIParam";
	const char* const kInitText = "Tsgrrreat";
	constexpr Vector2 kInitPos{ 300.0f,400.0f };

	const char* const kSelectExitText = "Exit";
	constexpr int kLogoPathID = 0;
}
IngameHudScreen::IngameHudScreen():
	m_pButton(nullptr)
{
}

void IngameHudScreen::Init()
{
	auto data = Data::Csv::LoadCsvAs<UITextParam>(kDataName);
	auto frameHandle = ImageManager::GetInstance().GetImage(kLogoPathID);
	auto startText = std::make_unique <UIText>(kSelectExitText, data[0], kInitPos);
	auto startImage = std::make_unique<UIImage>(frameHandle, kInitPos);
	m_pButton = CreateUIObject<UIButton>();
	m_pButton ->SetPosition(kInitPos);
	m_pButton->AddChild(std::move(startImage));
	m_pButton->AddChild(std::move(startText));
}
