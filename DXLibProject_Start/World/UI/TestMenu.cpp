#include "TestMenu.h"
#include<vector>
#include<string>
#include<DxLib.h>
#include"../../Utility/Color.h"
#include"../../Utility/Input.h"
#include"../../Utility/MyMath.h"
namespace {
	const char* const kMenuItemTexts[static_cast<int>(TestMenu::MenuItem::Max)]{
		"Game Start",
		"Option",
	};
	// カーソル座標のオフセット
	constexpr float kCursorOffset = -40;
	constexpr float kItemDistance = 20;
}
TestMenu::TestMenu():
	m_items(),
	m_selectIndex(0)
{
	Init();
}

void TestMenu::Init()
{
	int menuItemNum = static_cast<int>(TestMenu::MenuItem::Max);
	m_items.reserve(menuItemNum);
	for (size_t i = 0; i < menuItemNum; i++) {
		m_items.emplace_back(kMenuItemTexts[i]);
	}
}

void TestMenu::End()
{

}

void TestMenu::Update(float deltaTime)
{
	if (Input::IsPressed(Input::Button::Up, Input::Pad::P1))m_selectIndex--;
	if (Input::IsPressed(Input::Button::Down, Input::Pad::P1))m_selectIndex++;

	int menuMaxIndex = static_cast<int>(MenuItem::Max);
	m_selectIndex = (m_selectIndex + menuMaxIndex) % menuMaxIndex;
}

void TestMenu::Draw()
{
	if (!m_visible)return;

	for (size_t i = 0; i < m_items.size(); i++) {
		int drawX = static_cast<int>(m_position.x);
		int drawY = static_cast<int>(m_position.y+(i* kItemDistance));
		if (i == m_selectIndex) {
			DrawString(drawX +kCursorOffset, drawY, ">", Color::kBlack);
		}
		// メニューの表示
		DrawString(drawX, drawY, m_items[i].c_str(), Color::kBlack);
	}

}

const TestMenu::MenuItem& TestMenu::GetSelectItem()
{
	return static_cast<MenuItem>(m_selectIndex);
}
