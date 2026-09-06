#include "pch.h"
#include "ScreenManager.h"
#include"Screen.h"
ScreenManager::ScreenManager()
{

}

ScreenManager::~ScreenManager()
{

}

void ScreenManager::Update(float deltaTime, const InputData& inputData)
{
	// 管理しているUIScreenが空なら即時return
	if (Empty())return;
	// 最前面のUIScreenを更新する
	m_screens.back()->Update(deltaTime,inputData);
}

void ScreenManager::Draw()
{
	for (auto& screen : m_screens) {
		screen->Draw();
	}
}

void ScreenManager::PushScreen(std::unique_ptr<Screen> pScreen)
{
	// 渡されたUIScreenがnullptrなら即時return
	if (!pScreen)return;

	// 初期化
	pScreen->Init();
	// UIScreenを末尾に登録
	m_screens.emplace_back(std::move(pScreen));

}

void ScreenManager::PopScreen()
{
	// 管理しているUIScreenが空なら即時return
	if (Empty())return;
	// 管理しているUIScreenの末尾を削除
	m_screens.pop_back();
}

Screen* ScreenManager::GetTopScreen()
{
	// 管理しているUIScreenが空なら即時return
	if (Empty())return nullptr;
	// 最前面のUIScreenの生ポインタを返す
	return m_screens.back().get();
}

UI::Command ScreenManager::ConsumeCommand()
{
	if (m_screens.empty())return UI::Command::None;
	return m_screens.back()->ConsumeCommand();
}
