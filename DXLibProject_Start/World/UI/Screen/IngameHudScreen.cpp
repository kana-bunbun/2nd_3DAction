#include "IngameHudScreen.h"
#include"../../../Utility/Loder/CsvLoader.h"
#include"../../../Data/UITextParam.h"
namespace {
	const char* const kDataname="aa";
}
IngameHudScreen::IngameHudScreen():
	m_pButton(nullptr)
{
}

void IngameHudScreen::Init()
{
	auto data = Data::Csv::LoadCsvAs<UITextParam>(kDataname);

}
