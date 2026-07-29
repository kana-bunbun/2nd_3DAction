#include "SceneUITest.h"
#include "../SceneSelectDebug.h"
#include<DxLib.h>
#include<memory>
#include<vector>
#include<string>
#include"../Utility/Color.h"
#include"../Utility/MyMath.h"
#include"../Utility/Input.h"
#include"../World/UI/TitleLogo.h"
#include"../World/UI/TestText.h"
#include"../World/UI/TestMenu.h"
#include"../SceneTest.h"
namespace {
	constexpr Vector2 kInitLogpPos = { 1000.0f,500.0f };
	constexpr Vector2 kInitTextPos = { 1000.0f,600.0f };
}
SceneUITest::SceneUITest()
{

}

void SceneUITest::Init()
{
	m_pLogo = std::make_unique<TitleLogo>();
	m_pText = std::make_unique<TestText>();
	m_pTestMenu= std::make_unique<TestMenu>();
	m_pLogo->SetPosition(kInitLogpPos);
	m_pText->SetPosition(kInitTextPos);
	m_pTestMenu->SetPosition(kInitTextPos);
	m_pTestMenu->SetVisible(false);
	// フェード開始処理
	SceneBase::StartFadeIn();



}

void SceneUITest::End()
{

}

std::unique_ptr<SceneBase> SceneUITest::Update(float deltaTime)
{
	if (Input::IsPressed(Input::Button::Back, Input::Pad::P1))
		return std::make_unique<SceneSelectDebug>();

	m_pLogo->Update(deltaTime);
	switch (m_state)
	{
	case SceneUITest::SceneState::PressAnyButton:
		m_pText->Update(deltaTime);
		if (!Input::IsPressed(Input::Button::B, Input::Pad::P1))break;
		m_pText->SetVisible(false);
		m_pTestMenu->SetVisible(true);
		m_state = SceneState::MenuSelect;
		break;
	case SceneUITest::SceneState::MenuSelect:
		m_pTestMenu->Update(deltaTime);
		if (Input::IsPressed(Input::Button::A, Input::Pad::P1)) {
			m_pText->SetVisible(true);
			m_pTestMenu->SetVisible(false);
			m_state = SceneState::PressAnyButton;
		}
		if (!Input::IsPressed(Input::Button::B, Input::Pad::P1)) break;
		switch (m_pTestMenu->GetSelectItem())
		{
		case TestMenu::MenuItem::GameStart:
			return std::make_unique<SceneTest>();
		case TestMenu::MenuItem::Option:
		default:
			break;
		}
		break;
	case SceneUITest::SceneState::Max:
		break;
	default:
		break;
	}

	return nullptr;
}

void SceneUITest::Draw()
{
	DrawString(130, 130, "SceneUITest", Color::kWhite);
	m_pLogo->Draw();
	m_pText->Draw();
	m_pTestMenu->Draw();
}
