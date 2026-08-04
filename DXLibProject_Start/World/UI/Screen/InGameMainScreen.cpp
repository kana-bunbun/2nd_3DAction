#include "InGameMainScreen.h"
#include"../Object/UIItemSlot.h"
#include"../Group/UIItemList.h"

InGameMainScreen::InGameMainScreen():
	m_pItemList(nullptr)
{

}

InGameMainScreen::~InGameMainScreen()
{

}

void InGameMainScreen::Init()
{
	//auto data = Data::Csv::LoadCsvAs<UITextParam>(kDataName);
	//auto frameHandle = ImageManager::GetInstance().GetImage(kLogoPathID);
	//auto startText = std::make_unique <UIText>(kSelectExitText, data[0], kInitPos);
	//auto startImage = std::make_unique<UIImage>(frameHandle, kInitPos);
	CreateUIObject<UIItemList>();

}

void InGameMainScreen::Update(float deltaTime, const UIInput& input)
{
	//if ();
	UIScreen::Update(deltaTime,input);
}
